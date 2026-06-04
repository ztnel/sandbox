#pragma once

#include "static_span.h"
#include <stddef.h>

// Helper to construct StaticSpan from C-style array
template <typename T, size_t N>
static inline StaticSpan<T> make_static_span(T (&arr)[N]) {
    return StaticSpan<T>(arr, N);
}
