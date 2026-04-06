/**
 * @file i_gpio_output.hpp
 * @brief Interface for GPIO output devices
 *
 * Pure-virtual interface representing a read-write GPIO output.
 */

#pragma once

class IGpioOutput {
public:
    /**
     * @brief Destroy the IGpioOutput object
     */
    virtual ~IGpioOutput() = default;

    /**
     * @brief Get the current state of the GPIO output
     * @return bool True if high, false if low
     */
    virtual bool get_state() const = 0;

    /**
     * @brief Set the state of the GPIO output
     * @param[in] state Desired state (true=high, false=low)
     * @return void
     */
    virtual void set_state(bool state) = 0;
};
