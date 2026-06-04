#include "service_manager.h"
#include <vector>
#include <map>
#include <string>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

namespace Services {

struct ProfileData {
    uint64_t count;
    uint64_t total_us;
    uint64_t max_us;
    ProfileData(): count(0), total_us(0), max_us(0) {}
};

static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
static std::map<std::string, ProfileData> g_profiles;

static uint64_t now_us() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000000ULL + (uint64_t)tv.tv_usec;
}

ServiceManager::ServiceManager(IPollable** pollables, size_t npoll, const char** pollable_names,
                               IEventDriven** events, size_t nevents, const char** event_names,
                               IISRHandler** isrs, size_t nisrs, const char** isr_names)
    : pollables_(pollables), npoll_(npoll), pollable_names_(pollable_names),
      events_(events), nevents_(nevents), event_names_(event_names),
      isrs_(isrs), nisrs_(nisrs), isr_names_(isr_names)
{
    // Initialize profile entries from provided names
    pthread_mutex_lock(&g_mutex);
    if (pollable_names_) {
        for (size_t i = 0; i < npoll_; ++i) {
            if (pollable_names_[i]) g_profiles[std::string(pollable_names_[i])] = ProfileData();
        }
    } else {
        g_profiles[std::string("pollable")] = ProfileData();
    }
    if (event_names_) {
        for (size_t i = 0; i < nevents_; ++i) {
            if (event_names_[i]) g_profiles[std::string(event_names_[i])] = ProfileData();
        }
    } else {
        g_profiles[std::string("eventtask")] = ProfileData();
    }
    if (isr_names_) {
        for (size_t i = 0; i < nisrs_; ++i) {
            if (isr_names_[i]) g_profiles[std::string(isr_names_[i])] = ProfileData();
        }
    } else {
        g_profiles[std::string("isr")] = ProfileData();
    }
    pthread_mutex_unlock(&g_mutex);
}

void ServiceManager::isrNotify(const char* name) {
    pthread_mutex_lock(&g_mutex);
    std::string k(name);
    ProfileData &p = g_profiles[k];
    p.count += 1; // record event occurrence
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
            // attribute to provided name if available
            const char* nm = (isr_names_ && isr_names_[i]) ? isr_names_[i] : "isr";
            ProfileData &p = g_profiles[std::string(nm)];
            p.count += 1;
            p.total_us += dt;
            if (dt > p.max_us) p.max_us = dt;
            pthread_mutex_unlock(&g_mutex);
        }
    }
}

void ServiceManager::processAll() {
    for (size_t i = 0; i < npoll_; ++i) {
        IPollable* s = pollables_[i];
        if (!s) continue;
        uint64_t t0 = now_us();
        s->process();
        uint64_t t1 = now_us();
        uint64_t dt = (t1 > t0) ? (t1 - t0) : 0;
        pthread_mutex_lock(&g_mutex);
        const char* nm = (pollable_names_ && pollable_names_[i]) ? pollable_names_[i] : "pollable";
        ProfileData &p = g_profiles[std::string(nm)];
        p.count += 1;
        p.total_us += dt;
        if (dt > p.max_us) p.max_us = dt;
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
    for (std::map<std::string, ProfileData>::const_iterator it = g_profiles.begin(); it != g_profiles.end(); ++it) {
        const ProfileData &p = it->second;
        double avg = (p.count > 0) ? (double)p.total_us / (double)p.count : 0.0;
        printf("  %s: count=%llu total_us=%llu avg=%.2f max_us=%llu\n",
               it->first.c_str(), (unsigned long long)p.count, (unsigned long long)p.total_us, avg, (unsigned long long)p.max_us);
    }
    pthread_mutex_unlock(&g_mutex);
}

} // namespace Services
