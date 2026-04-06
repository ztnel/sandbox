/**
 * @file i_async_service.hpp
 * @brief Interface for asynchronous services running on independent timelines.
 *
 * Asynchronous services provide `start()` and `stop()` lifecycle methods
 * and are typically driven by interrupts or separate schedulers.
 */

#pragma once

#include "i_service.hpp"

/**
 * @brief Interface for asynchronous services.
 */
class IAsyncService : public IService {
public:
    /**
     * @brief Start the asynchronous service.
     * @return True if the service started successfully, false otherwise.
     */
    virtual bool start() = 0;

    /**
     * @brief Stop the asynchronous service.
     */
    virtual void stop() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~IAsyncService() = default;
};