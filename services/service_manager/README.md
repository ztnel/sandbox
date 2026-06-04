Service Manager Prototype

This prototype demonstrates a minimal C++03 framework to manage two kinds of services:
- Pollable services: implement IPollable::process() and are driven from the main loop
- Event-driven services: implement IEventDriven::start()/stop() and run as background tasks

All registration and a simple profiler are implemented in a single source file (src/service_manager.cpp).

Build
  mkdir -p build && cd build
  cmake ../../services/service_manager
  make

Run
  ./example_main

Notes
- This is a host-side prototype. ISR-safety is simulated; the current isrNotify() uses a mutex and is not lock-free.
- Profile aggregation is centralized in service_manager.cpp. For a baremetal port, replace locking and dynamic containers with static, lock-free structures.
