/**
 * @file slew_rate_limiter.cpp
 * @brief Implements slew-rate limiting behavior for domain control logic.
 */

#include "slew_rate_limiter.hpp"

SlewRateLimiter::SlewRateLimiter(float max_delta_per_step)
    : max_delta_per_step(max_delta_per_step), state(0.0f), initialized(false) {
}

float SlewRateLimiter::step(float target_value) {
    float next_state = target_value;

    if (!this->initialized) {
        this->initialized = true;
    } else {
        const float delta = target_value - this->state;
        if (delta > this->max_delta_per_step) {
            next_state = this->state + this->max_delta_per_step;
        } else if (delta < -this->max_delta_per_step) {
            next_state = this->state - this->max_delta_per_step;
        }
    }

    this->state = next_state;
    return this->state;
}

float SlewRateLimiter::value() const {
    return this->state;
}

void SlewRateLimiter::reset(float initial_value) {
    this->state = initial_value;
    this->initialized = true;
}
