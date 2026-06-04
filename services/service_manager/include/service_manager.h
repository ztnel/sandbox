#pragma once

#include "interfaces.h"
#include <stdint.h>
#include <stddef.h>

namespace Services {

class ServiceManager {
public:
    ServiceManager(IPollable** pollables, size_t npoll, const char** pollable_names,
                   IEventDriven** events, size_t nevents, const char** event_names,
                   IISRHandler** isrs, size_t nisrs, const char** isr_names);

    // Main-loop operations
    void processAll();

    // Event-driven control
    void startAllEventDriven();
    void stopAllEventDriven();

    // ISR invocation (called from ISR context in prototype)
    void invokeISRHandlers();

    // Simple profiling output
    void printProfiles();

    // ISR-safe notification (prototype)
    void isrNotify(const char* name);

private:
    IPollable** pollables_;
    size_t npoll_;
    const char** pollable_names_;

    IEventDriven** events_;
    size_t nevents_;
    const char** event_names_;

    IISRHandler** isrs_;
    size_t nisrs_;
    const char** isr_names_;

    // opaque internal state (implemented in cpp)
};

} // namespace Services
