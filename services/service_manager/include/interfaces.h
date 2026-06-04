#pragma once

namespace Services {

class IService {
public:
    virtual ~IService() {}
    // Initialization hook for services; made pure-virtual per review
    virtual void init() = 0;
};

class IPollable : public IService {
public:
    virtual void process() = 0;
    virtual ~IPollable() {}
};

class IEventDriven : public IService {
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~IEventDriven() {}
};

// ISR handler interface: implementations must be short and ISR-safe.
// Note: IPollable::process() is intended for main-loop polling and may perform
// longer work. IISRHandler::onISR() is explicitly constrained for ISR context
// (no allocations, minimal inlining). Keep both to make intent explicit.
class IISRHandler : public IService {
public:
    virtual void onISR() = 0;
    virtual ~IISRHandler() {}
};

} // namespace Services
