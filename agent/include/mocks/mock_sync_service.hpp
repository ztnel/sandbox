/**
 * @file mock_sync_service.hpp
 * @brief GoogleMock mock for `ISyncService`.
 */

#pragma once

#include "i_sync_service.hpp"
#include <gmock/gmock.h>

/**
 * @brief Mock implementation of ISyncService for testing.
 */
class MockSyncService : public ISyncService {
public:
    MOCK_METHOD(bool, init, (), (override));
    MOCK_METHOD(bool, is_running, (), (override));
    MOCK_METHOD(bool, is_healthy, (), (override));
    MOCK_METHOD(bool, process, (), (override));
};