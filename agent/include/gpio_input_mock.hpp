/**
 * @file gpio_input_mock.hpp
 * @brief GoogleMock mock for IGpioInput
 *
 * Provides a mock implementation of IGpioInput for unit tests.
 */

#pragma once

#include <gmock/gmock.h>
#include "i_gpio_input.hpp"

class GpioInputMock : public IGpioInput {
public:
    GpioInputMock() = default;
    virtual ~GpioInputMock() = default;

    /**
     * @brief Mocked get_state method
     * @return bool Current mock state
     */
    MOCK_METHOD(bool, get_state, (), (const, override));
};
