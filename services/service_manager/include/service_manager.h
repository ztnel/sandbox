#pragma once

#include "interfaces.h"
#include <stdint.h>
#include <stddef.h>

namespace Services {

class ServiceManager {
public:
    // Constructor takes pointers and counts (C++03-compatible "span" emulation).
    ServiceManager(IPollable** pollables, size_t npoll,
                   IEventDriven** events, size_t nevents,
                   IISRHandler** isrs, size_t nisrs);

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

    IEventDriven** events_;
    size_t nevents_;

    IISRHandler** isrs_;
    size_t nisrs_;

    // opaque internal state (implemented in cpp)
};

} // namespace Services
