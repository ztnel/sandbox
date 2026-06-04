#pragma once

#include <stddef.h>

// C++03-compatible lightweight span (pointer+size)
template <typename T>
class StaticSpan {
public:
    StaticSpan(T* data = 0, size_t size = 0) : data_(data), size_(size) {}
    T* data() const { return data_; }
    size_t size() const { return size_; }
    T& operator[](size_t i) const { return data_[i]; }
private:
    T* data_;
    size_t size_;
};

// Helper to construct StaticSpan from C-style array
template <typename T, size_t N>
static inline StaticSpan<T> make_static_span(T (&arr)[N]) {
    return StaticSpan<T>(arr, N);
}
