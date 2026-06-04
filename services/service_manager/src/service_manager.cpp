#include "service_manager.h"
#include <vector>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

namespace Services {

struct ProfileData {
    volatile unsigned long long count;
    volatile unsigned long long total_us;
    volatile unsigned long long max_us;
    ProfileData(): count(0), total_us(0), max_us(0) {}
};

static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

// Fixed-size profile storage for baremetal-safety prototype
static const int MAX_PROFILES = 128;
static ProfileData g_profiles_arr[MAX_PROFILES];
static char g_profile_names[MAX_PROFILES][32];
static int g_profile_count = 0;

// Atomic helpers using GCC/Clang builtins for C++03 compatibility
static inline unsigned long long atomic_load_ull(volatile unsigned long long* v) {
    return __sync_fetch_and_add(v, 0ULL);
}

static inline void atomic_add_ull(volatile unsigned long long* v, unsigned long long delta) {
    __sync_fetch_and_add(v, delta);
}

static inline void atomic_max_ull(volatile unsigned long long* v, unsigned long long vnew) {
    unsigned long long prev = atomic_load_ull(v);
    while (vnew > prev && !__sync_bool_compare_and_swap(v, prev, vnew)) {
        prev = atomic_load_ull(v);
    }
}

static int find_profile(const char* name) {
    for (int i = 0; i < g_profile_count; ++i) {
        if (strcmp(g_profile_names[i], name) == 0) return i;
    }
    return -1;
}

static int add_profile(const char* name) {
    if (g_profile_count >= MAX_PROFILES) return -1;
    strncpy(g_profile_names[g_profile_count], name, sizeof(g_profile_names[g_profile_count]) - 1);
    g_profile_names[g_profile_count][sizeof(g_profile_names[g_profile_count]) - 1] = '\0';
    // zero-initialize profile data
    g_profiles_arr[g_profile_count] = ProfileData();
    ++g_profile_count;
    return g_profile_count - 1;
}

static uint64_t now_us() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000000ULL + (uint64_t)tv.tv_usec;
}

ServiceManager::ServiceManager(StaticSpan<IPollable*> pollables,
                               StaticSpan<IEventDriven*> events,
                               StaticSpan<IISRHandler*> isrs)
    : pollables(pollables), events(events), isrs(isrs)
{
    // Initialize profile entries with generated names
    pthread_mutex_lock(&g_mutex);
    char buf[64];
    for (size_t i = 0; i < this->pollables.size(); ++i) {
        snprintf(buf, sizeof(buf), "pollable%u", (unsigned)i);
        add_profile(buf);
    }
    for (size_t i = 0; i < this->events.size(); ++i) {
        snprintf(buf, sizeof(buf), "eventtask%u", (unsigned)i);
        add_profile(buf);
    }
    for (size_t i = 0; i < this->isrs.size(); ++i) {
        snprintf(buf, sizeof(buf), "isr%u", (unsigned)i);
        add_profile(buf);
    }
    pthread_mutex_unlock(&g_mutex);
}

void ServiceManager::isrNotify(const char* name) {
    int idx = find_profile(name);
    if (idx < 0) {
        // profile table may need expanding; do under lock once
        pthread_mutex_lock(&g_mutex);
        idx = find_profile(name);
        if (idx < 0) idx = add_profile(name);
        pthread_mutex_unlock(&g_mutex);
    }
    if (idx >= 0) atomic_add_ull(&g_profiles_arr[idx].count, 1ULL);
}

void ServiceManager::invokeISRHandlers() {
    // Call ISR handlers without locking registrations (registrations are static in this model)
    for (size_t i = 0; i < isrs.size(); ++i) {
        IISRHandler* h = isrs[i];
        if (h) {
            uint64_t t0 = now_us();
            h->onISR();
            uint64_t t1 = now_us();
            uint64_t dt = (t1 > t0) ? (t1 - t0) : 0;
            char buf[64];
            snprintf(buf, sizeof(buf), "isr%u", (unsigned)i);
            int idx = find_profile(buf);
            if (idx >= 0) {
                // Lock-free updates: count and totals updated atomically
                atomic_add_ull(&g_profiles_arr[idx].count, 1ULL);
                atomic_add_ull(&g_profiles_arr[idx].total_us, dt);
                atomic_max_ull(&g_profiles_arr[idx].max_us, dt);
            }
        }
    }
}

void ServiceManager::processAll() {
    char buf[64];
    for (size_t i = 0; i < pollables.size(); ++i) {
        IPollable* s = pollables[i];
        if (!s) continue;
        uint64_t t0 = now_us();
        s->process();
        uint64_t t1 = now_us();
        uint64_t dt = (t1 > t0) ? (t1 - t0) : 0;
        snprintf(buf, sizeof(buf), "pollable%u", (unsigned)i);
        int idx = find_profile(buf);
        if (idx >= 0) {
            atomic_add_ull(&g_profiles_arr[idx].count, 1ULL);
            atomic_add_ull(&g_profiles_arr[idx].total_us, dt);
            atomic_max_ull(&g_profiles_arr[idx].max_us, dt);
        }
    }
}

void ServiceManager::startAllEventDriven() {
    for (size_t i = 0; i < events.size(); ++i) {
        if (events[i]) events[i]->start();
    }
}

void ServiceManager::stopAllEventDriven() {
    for (size_t i = 0; i < events.size(); ++i) {
        if (events[i]) events[i]->stop();
    }
}

void ServiceManager::printProfiles() {
    printf("Profiles:\n");
    for (int i = 0; i < g_profile_count; ++i) {
        unsigned long long cnt = atomic_load_ull(&g_profiles_arr[i].count);
        unsigned long long total = atomic_load_ull(&g_profiles_arr[i].total_us);
        unsigned long long maxv = atomic_load_ull(&g_profiles_arr[i].max_us);
        double avg = (cnt > 0) ? (double)total / (double)cnt : 0.0;
        printf("  %s: count=%llu total_us=%llu avg=%.2f max_us=%llu\n",
               g_profile_names[i], (unsigned long long)cnt, (unsigned long long)total, avg, (unsigned long long)maxv);
    }
}

} // namespace Services
