/**
 * @file i_sync_service.hpp
 * @brief Interface for synchronous services run on main loop ticks.
 *
 * Synchronous services implement `process()` which is executed during the
 * main process tick.
 */

#pragma once

#include "i_service.hpp"

/**
 * @brief Interface for synchronous services.
 */
class ISyncService : public IService {
public:
    /**
     * @brief Process a single tick of the service.
     * @return True if the process tick succeeded, false otherwise.
     */
    virtual bool process() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ISyncService() = default;
};