/**
 * @file mock_time_source.hpp
 * @brief GMock mock of the ITimeSource interface.
 *
 * This header is intentionally placed in the public include tree so that
 * downstream projects consuming this library can include it in their own
 * unit tests to mock timing dependencies.
 */

#pragma once

#include "i_time_source.hpp"

#include <gmock/gmock.h>

/**
 * @brief Google-Mock implementation of ITimeSource for unit testing.
 */
class MockTimeSource : public ITimeSource {
public:
    MOCK_METHOD(uint32_t, get_ticks, (), (const, override));
    MOCK_METHOD(uint32_t, get_time_s, (), (const, override));
    MOCK_METHOD(uint32_t, get_time_ms, (), (const, override));
    MOCK_METHOD(uint32_t, get_time_us, (), (const, override));
    MOCK_METHOD(uint32_t, get_time_ns, (), (const, override));

    MOCK_METHOD(bool, has_elapsed_s, (uint32_t start_ticks, uint32_t duration_s), (const, override));
    MOCK_METHOD(bool, has_elapsed_ms, (uint32_t start_ticks, uint32_t duration_ms), (const, override));
    MOCK_METHOD(bool, has_elapsed_us, (uint32_t start_ticks, uint32_t duration_us), (const, override));
    MOCK_METHOD(bool, has_elapsed_ns, (uint32_t start_ticks, uint32_t duration_ns), (const, override));
};
