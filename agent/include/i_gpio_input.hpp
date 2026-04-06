/**
 * @file i_gpio_input.hpp
 * @brief Interface for GPIO input devices
 *
 * Pure-virtual interface representing a read-only GPIO input.
 */

#pragma once

class IGpioInput {
public:
    /**
     * @brief Destroy the IGpioInput object
     */
    virtual ~IGpioInput() = default;

    /**
     * @brief Get the current state of the GPIO input
     * @return bool True if high, false if low
     */
    virtual bool get_state() const = 0;
};
