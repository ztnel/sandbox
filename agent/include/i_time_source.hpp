/**
 * @file i_time_source.hpp
 * @brief Pure abstract interface for a global timing module.
 *
 * Provides a hardware-independent abstraction over timestamp retrieval
 * and non-blocking elapsed-time checks.  Implementations wrap a concrete
 * hardware counter (e.g. SysTick, TIM) while consumers depend only on
 * this interface, enabling deterministic unit-testing through mocks.
 */

#pragma once

#include <stdint.h>

/**
 * @brief Hardware-independent timing interface.
 *
 * @details All tick and time values use unsigned 32-bit integers.
 * Implementations must handle counter wrap-around correctly in the
 * has_elapsed family of methods (unsigned subtraction naturally handles
 * a single wrap when start > current).
 */
class ITimeSource {
public:
    virtual ~ITimeSource() = default;

    /**
     * @brief Returns the current raw hardware counter value.
     * @return Current tick count.
     */
    virtual uint32_t get_ticks() const = 0;

    /**
     * @brief Returns the current timestamp expressed in seconds.
     * @return Elapsed time in seconds since an implementation-defined epoch.
     */
    virtual uint32_t get_time_s() const = 0;

    /**
     * @brief Returns the current timestamp expressed in milliseconds.
     * @return Elapsed time in milliseconds since an implementation-defined epoch.
     */
    virtual uint32_t get_time_ms() const = 0;

    /**
     * @brief Returns the current timestamp expressed in microseconds.
     * @return Elapsed time in microseconds since an implementation-defined epoch.
     */
    virtual uint32_t get_time_us() const = 0;

    /**
     * @brief Returns the current timestamp expressed in nanoseconds.
     * @return Elapsed time in nanoseconds since an implementation-defined epoch.
     */
    virtual uint32_t get_time_ns() const = 0;

    /**
     * @brief Checks whether the given duration in seconds has elapsed.
    * @param start_ticks Tick value captured at the beginning of the interval.
    * @param duration_s  Duration to check in seconds.
     * @return true if at least duration_s seconds have passed since start_ticks.
     */
    virtual bool has_elapsed_s(uint32_t start_ticks, uint32_t duration_s) const = 0;

    /**
     * @brief Checks whether the given duration in milliseconds has elapsed.
    * @param start_ticks Tick value captured at the beginning of the interval.
    * @param duration_ms Duration to check in milliseconds.
     * @return true if at least duration_ms milliseconds have passed since start_ticks.
     */
    virtual bool has_elapsed_ms(uint32_t start_ticks, uint32_t duration_ms) const = 0;

    /**
     * @brief Checks whether the given duration in microseconds has elapsed.
    * @param start_ticks Tick value captured at the beginning of the interval.
    * @param duration_us Duration to check in microseconds.
     * @return true if at least duration_us microseconds have passed since start_ticks.
     */
    virtual bool has_elapsed_us(uint32_t start_ticks, uint32_t duration_us) const = 0;

    /**
     * @brief Checks whether the given duration in nanoseconds has elapsed.
    * @param start_ticks Tick value captured at the beginning of the interval.
    * @param duration_ns Duration to check in nanoseconds.
     * @return true if at least duration_ns nanoseconds have passed since start_ticks.
     */
    virtual bool has_elapsed_ns(uint32_t start_ticks, uint32_t duration_ns) const = 0;
};
