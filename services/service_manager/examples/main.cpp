#include "service_manager.h"
#include "interfaces.h"
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

using namespace Services;

// Simple pollable service
class Poller : public IPollable {
public:
    void process() {
        // simulate some work
        for (volatile int i=0;i<10000;++i) {}
    }
};

// Simple event-driven service that runs in a thread
class EventTask : public IEventDriven {
public:
    pthread_t thread;
    bool running;
    static void* threadFn(void* arg) {
        EventTask* self = (EventTask*)arg;
        while (self->running) {
            // simulate background work
            for (volatile int i=0;i<20000;++i) {}
            usleep(10000);
        }
        return NULL;
    }
    EventTask(): running(false) {}
    void start() {
        running = true;
        pthread_create(&thread, NULL, threadFn, this);
    }
    void stop() {
        running = false;
        pthread_join(thread, NULL);
    }
};

// ISR handler example: must be short
class ISRHandler : public IISRHandler {
public:
    void onISR() {
        // quick operation
        for (volatile int i=0;i<1000;++i) {}
    }
};

static pthread_t isr_thread;
static bool isr_running = false;
static void* isr_sim_fn(void* arg) {
    ServiceManager* mgr = (ServiceManager*)arg;
    while (isr_running) {
        mgr->invokeISRHandlers();
        usleep(2000); // simulate frequent ISR
    }
    return NULL;
}

int main() {
    Poller p;
    EventTask e;
    ISRHandler h;

    IPollable* pollables[] = { &p };
    const char* pollable_names[] = { "poller" };

    IEventDriven* events[] = { &e };
    const char* event_names[] = { "eventtask" };

    IISRHandler* isrs[] = { &h };
    const char* isr_names[] = { "isr_handler" };

    ServiceManager mgr(pollables, 1, pollable_names,
                       events, 1, event_names,
                       isrs, 1, isr_names);

    // start backgrounds
    mgr.startAllEventDriven();
    isr_running = true;
    pthread_create(&isr_thread, NULL, isr_sim_fn, &mgr);

    for (int i = 0; i < 200; ++i) {
        mgr.processAll();
        usleep(5000);
        if (i % 50 == 0) {
            // simulate software ISR notification
            mgr.isrNotify("poller");
        }
    }

    // stop
    isr_running = false;
    pthread_join(isr_thread, NULL);
    mgr.stopAllEventDriven();

    mgr.printProfiles();
    return 0;
}
