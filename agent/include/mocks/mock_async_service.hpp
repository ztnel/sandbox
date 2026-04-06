/**
 * @file mock_async_service.hpp
 * @brief GoogleMock mock for `IAsyncService`.
 */

#pragma once

#include "i_async_service.hpp"
#include <gmock/gmock.h>

/**
 * @brief Mock implementation of IAsyncService for testing.
 */
class MockAsyncService : public IAsyncService {
public:
    MOCK_METHOD(bool, init, (), (override));
    MOCK_METHOD(bool, is_running, (), (override));
    MOCK_METHOD(bool, is_healthy, (), (override));
    MOCK_METHOD(bool, start, (), (override));
    MOCK_METHOD(void, stop, (), (override));
};