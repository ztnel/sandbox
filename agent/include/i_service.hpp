/**
 * @file i_service.hpp
 * @brief Common base interface for all services.
 *
 * Provides the core service lifecycle methods used by both synchronous
 * and asynchronous service types.
 */

#pragma once

/**
 * @brief Common base interface for all services.
 */
class IService {
public:
    /**
     * @brief Initialize the service.
     * @return True if initialization is successful, false otherwise.
     */
    virtual bool init() = 0;

    /**
     * @brief Check if the service is currently running.
     * @return True if the service is running, false otherwise.
     */
    virtual bool is_running() = 0;

    /**
     * @brief Check if the service is healthy.
     * @return True if the service is healthy, false otherwise.
     */
    virtual bool is_healthy() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~IService() = default;
};