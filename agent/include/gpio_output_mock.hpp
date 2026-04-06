/**
 * @file gpio_output_mock.hpp
 * @brief GoogleMock mock for IGpioOutput
 *
 * Provides a mock implementation of IGpioOutput for unit tests.
 */

#pragma once

#include <gmock/gmock.h>
#include "i_gpio_output.hpp"

class GpioOutputMock : public IGpioOutput {
public:
    GpioOutputMock() = default;
    virtual ~GpioOutputMock() = default;

    MOCK_METHOD(bool, get_state, (), (const, override));
    MOCK_METHOD(void, set_state, (bool state), (override));
};
