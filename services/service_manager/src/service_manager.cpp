#include "service_manager.h"
#include <vector>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

namespace Services {

struct ProfileData {
    uint64_t count;
    uint64_t total_us;
    uint64_t max_us;
    ProfileData(): count(0), total_us(0), max_us(0) {}
};

static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

// Fixed-size profile storage for baremetal-safety prototype
static const int MAX_PROFILES = 128;
static ProfileData g_profiles_arr[MAX_PROFILES];
static char g_profile_names[MAX_PROFILES][32];
static int g_profile_count = 0;

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

ServiceManager::ServiceManager(IPollable** pollables, size_t npoll,
                               IEventDriven** events, size_t nevents,
                               IISRHandler** isrs, size_t nisrs)
    : pollables_(pollables), npoll_(npoll),
      events_(events), nevents_(nevents),
      isrs_(isrs), nisrs_(nisrs)
{
    // Initialize profile entries with generated names (no name arrays in C++03)
    pthread_mutex_lock(&g_mutex);
    char buf[64];
    for (size_t i = 0; i < npoll_; ++i) {
        snprintf(buf, sizeof(buf), "pollable%u", (unsigned)i);
        add_profile(buf);
    }
    for (size_t i = 0; i < nevents_; ++i) {
        snprintf(buf, sizeof(buf), "eventtask%u", (unsigned)i);
        add_profile(buf);
    }
    for (size_t i = 0; i < nisrs_; ++i) {
        snprintf(buf, sizeof(buf), "isr%u", (unsigned)i);
        add_profile(buf);
    }
    pthread_mutex_unlock(&g_mutex);
}

void ServiceManager::isrNotify(const char* name) {
    pthread_mutex_lock(&g_mutex);
    int idx = find_profile(name);
    if (idx < 0) idx = add_profile(name);
    if (idx >= 0) g_profiles_arr[idx].count += 1; // record event occurrence
    pthread_mutex_unlock(&g_mutex);
}

void ServiceManager::invokeISRHandlers() {
    // Call ISR handlers without locking registrations (registrations are static in this model)
    for (size_t i = 0; i < nisrs_; ++i) {
        IISRHandler* h = isrs_[i];
        if (h) {
            uint64_t t0 = now_us();
            h->onISR();
            uint64_t t1 = now_us();
            uint64_t dt = (t1 > t0) ? (t1 - t0) : 0;
            pthread_mutex_lock(&g_mutex);
            char buf[64];
            snprintf(buf, sizeof(buf), "isr%u", (unsigned)i);
            int idx = find_profile(buf);
            if (idx >= 0) {
                ProfileData &p = g_profiles_arr[idx];
                p.count += 1;
                p.total_us += dt;
                if (dt > p.max_us) p.max_us = dt;
            }
            pthread_mutex_unlock(&g_mutex);
        }
    }
}

void ServiceManager::processAll() {
    char buf[64];
    for (size_t i = 0; i < npoll_; ++i) {
        IPollable* s = pollables_[i];
        if (!s) continue;
        uint64_t t0 = now_us();
        s->process();
        uint64_t t1 = now_us();
        uint64_t dt = (t1 > t0) ? (t1 - t0) : 0;
        pthread_mutex_lock(&g_mutex);
        snprintf(buf, sizeof(buf), "pollable%u", (unsigned)i);
        int idx = find_profile(buf);
        if (idx >= 0) {
            ProfileData &p = g_profiles_arr[idx];
            p.count += 1;
            p.total_us += dt;
            if (dt > p.max_us) p.max_us = dt;
        }
        pthread_mutex_unlock(&g_mutex);
    }
}

void ServiceManager::startAllEventDriven() {
    for (size_t i = 0; i < nevents_; ++i) {
        if (events_[i]) events_[i]->start();
    }
}

void ServiceManager::stopAllEventDriven() {
    for (size_t i = 0; i < nevents_; ++i) {
        if (events_[i]) events_[i]->stop();
    }
}

void ServiceManager::printProfiles() {
    pthread_mutex_lock(&g_mutex);
    printf("Profiles:\n");
    for (int i = 0; i < g_profile_count; ++i) {
        const ProfileData &p = g_profiles_arr[i];
        double avg = (p.count > 0) ? (double)p.total_us / (double)p.count : 0.0;
        printf("  %s: count=%llu total_us=%llu avg=%.2f max_us=%llu\n",
               g_profile_names[i], (unsigned long long)p.count, (unsigned long long)p.total_us, avg, (unsigned long long)p.max_us);
    }
    pthread_mutex_unlock(&g_mutex);
}

} // namespace Services
