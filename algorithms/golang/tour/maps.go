
package tour

import (
    "strings"
)

func WordCount(s string) map[string]int {
	wc := make(map[string]int)
	for _, word := range(strings.Fields(s)) {
		cnt, _ := wc[word]
		wc[word] = cnt+1;
	}
	return wc
}
