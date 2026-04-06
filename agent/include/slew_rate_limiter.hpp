/**
 * @file slew_rate_limiter.hpp
 * @brief Declares a simple slew-rate limiter used in converter control logic.
 */

#pragma once

/**
 * @brief Limits output slew to a configured maximum step delta.
 */
class SlewRateLimiter {
public:
    /**
     * @brief Creates a limiter with a maximum absolute change per call.
     * @param max_delta_per_step Maximum allowed delta on each step.
     */
    explicit SlewRateLimiter(float max_delta_per_step);

    /**
     * @brief Advances internal state toward the target while respecting slew limit.
     * @param target_value Desired target value.
     * @return The updated limiter output.
     */
    float step(float target_value);

    /**
     * @brief Gets the current limiter output value.
     * @return Current output value.
     */
    float value() const;

    /**
     * @brief Resets internal state to a known value.
     * @param initial_value Value used to initialize the internal state.
     */
    void reset(float initial_value = 0.0f);

private:
    float max_delta_per_step;
    float state;
    bool initialized;
};
