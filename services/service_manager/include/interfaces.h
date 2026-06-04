#pragma once

namespace Services {

class IService {
public:
    virtual ~IService() {}
    // Optional initialization hook for services
    virtual void init() {}
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

// ISR handler interface: implementations must be short and ISR-safe
class IISRHandler : public IService {
public:
    virtual void onISR() = 0;
    virtual ~IISRHandler() {}
};

} // namespace Services
