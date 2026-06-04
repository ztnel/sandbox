#include "service_manager.h"
#include "interfaces.h"
#include "platform.h"
#include <stdio.h>

using namespace Services;

// Simple pollable service
class Poller : public IPollable {
public:
    void init() {}
    void process() {
        // simulate some work
        for (volatile int i=0;i<10000;++i) {}
    }
};

// Simple event-driven service that runs in a thread
class EventTask : public IEventDriven {
public:
    platform_thread_t thread;
    bool running;
    static void* threadFn(void* arg) {
        EventTask* self = (EventTask*)arg;
        while (self->running) {
            // simulate background work
            for (volatile int i=0;i<20000;++i) {}
            platform_sleep_us(10000);
        }
        return NULL;
    }
    EventTask(): running(false) {}
    void init() {}
    void start() {
        running = true;
        platform_thread_create(&thread, threadFn, this);
    }
    void stop() {
        running = false;
        platform_thread_join(thread);
    }
};

// ISR handler example: must be short
class ISRHandler : public IISRHandler {
public:
    void init() {}
    void onISR() {
        // quick operation
        for (volatile int i=0;i<1000;++i) {}
    }
};

static platform_thread_t isr_thread;
static bool isr_running = false;
static void* isr_sim_fn(void* arg) {
    ServiceManager* mgr = (ServiceManager*)arg;
    while (isr_running) {
        mgr->invokeISRHandlers();
        platform_sleep_us(2000); // simulate frequent ISR
    }
    return NULL;
}

int main() {
    Poller p;
    EventTask e;
    ISRHandler h;

    IPollable* pollables_arr[] = { &p };
    StaticSpan<IPollable*> pollables(pollables_arr, 1);

    IEventDriven* events_arr[] = { &e };
    StaticSpan<IEventDriven*> events(events_arr, 1);

    IISRHandler* isrs_arr[] = { &h };
    StaticSpan<IISRHandler*> isrs(isrs_arr, 1);

    ServiceManager mgr(pollables, events, isrs);

    // start backgrounds
    mgr.startAllEventDriven();
    isr_running = true;
    platform_thread_create(&isr_thread, isr_sim_fn, &mgr);

    for (int i = 0; i < 200; ++i) {
        mgr.processAll();
        platform_sleep_us(5000);
        if (i % 50 == 0) {
            // simulate software ISR notification
            mgr.isrNotify("poller");
        }
    }

    // stop
    isr_running = false;
    platform_thread_join(isr_thread);
    mgr.stopAllEventDriven();

    mgr.printProfiles();
    return 0;
}
