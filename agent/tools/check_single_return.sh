#!/usr/bin/env sh

set -eu

if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <dir> [<dir> ...]"
    exit 2
fi

status=0
tmp_file="$(mktemp)"

find "$@" -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.cxx' -o -name '*.h' -o -name '*.hpp' \) > "$tmp_file"

while IFS= read -r file_path; do
    if ! awk '
        function open_count(text, t) {
            t = text
            return gsub(/\{/, "{", t)
        }

        function close_count(text, t) {
            t = text
            return gsub(/\}/, "}", t)
        }

        function has_return(text) {
            return match(text, /(^|[^[:alnum:]_])return([^[:alnum:]_]|$)/) != 0
        }

        BEGIN {
            in_function = 0
            depth = 0
            return_count = 0
            function_start = 0
            function_signature = ""
            local_status = 0
        }

        {
            line = $0
            sub(/\/\/.*$/, "", line)

            if (!in_function) {
                is_control = line ~ /^[[:space:]]*(if|for|while|switch|catch)[[:space:]]*\(/
                opens_block = line ~ /\)[[:space:]]*\{[[:space:]]*$/

                if (!is_control && opens_block) {
                    in_function = 1
                    depth = 1
                    return_count = has_return(line) ? 1 : 0
                    function_start = NR
                    function_signature = line
                }
            } else {
                if (has_return(line)) {
                    return_count += 1
                }

                depth += open_count(line)
                depth -= close_count(line)

                if (depth == 0) {
                    if (return_count > 1) {
                        printf("Single-return rule violation: %s:%d has %d return statements in one function.\\n", FILENAME, function_start, return_count)
                        local_status = 1
                    }

                    in_function = 0
                    return_count = 0
                    function_start = 0
                    function_signature = ""
                }
            }
        }

        END {
            exit local_status
        }
    ' "$file_path"; then
        status=1
    fi
done < "$tmp_file"

rm -f "$tmp_file"
exit "$status"
