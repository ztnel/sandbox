#pragma once

#include "interfaces.h"
#include "static_span.h"
#include <stdint.h>
#include <stddef.h>

namespace Services {

class ServiceManager {
public:
    // Constructor takes StaticSpan instances (pointer+size pairs) for C++03.
    ServiceManager(StaticSpan<IPollable*> pollables,
                   StaticSpan<IEventDriven*> events,
                   StaticSpan<IISRHandler*> isrs);

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
    IPollable** pollables;
    size_t npoll;

    IEventDriven** events;
    size_t nevents;

    IISRHandler** isrs;
    size_t nisrs;

    // opaque internal state (implemented in cpp)
};

} // namespace Services
