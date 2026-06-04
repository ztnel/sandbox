#pragma once

#ifdef __unix__
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

typedef pthread_t platform_thread_t;

static inline int platform_thread_create(platform_thread_t* out, void* (*fn)(void*), void* arg) {
    return pthread_create(out, NULL, fn, arg);
}

static inline int platform_thread_join(platform_thread_t thread) {
    return pthread_join(thread, NULL);
}

static inline void platform_sleep_us(unsigned int us) {
    usleep(us);
}

#else
// Baremetal stubs - replace with platform-specific implementations
typedef void* platform_thread_t;
static inline int platform_thread_create(platform_thread_t* out, void* (*fn)(void*), void* arg) { (void)out; (void)fn; (void)arg; return -1; }
static inline int platform_thread_join(platform_thread_t thread) { (void)thread; return -1; }
static inline void platform_sleep_us(unsigned int us) { (void)us; }
#endif
