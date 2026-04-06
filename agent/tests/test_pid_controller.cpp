/**
 * @file test_pid_controller.cpp
 * @brief Unit tests for PIDController
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "pid_controller.hpp"

/** @test Proportional action only */
TEST(PIDControllerTests, ProportionalOnly) {
    PIDController pid(2.0, 0.0, 0.0, 0.01);

    EXPECT_DOUBLE_EQ(pid.compute(1.0, 0.0), 2.0);
}

/** @test Integral accumulates across calls */
TEST(PIDControllerTests, IntegralAccumulation) {
    PIDController pid(0.0, 1.0, 0.0, 1.0);
    pid.reset();

    EXPECT_DOUBLE_EQ(pid.compute(1.0, 0.0), 1.0);
    EXPECT_DOUBLE_EQ(pid.compute(1.0, 0.0), 2.0);
}

/** @test Derivative responds to change in error */
TEST(PIDControllerTests, DerivativeAction) {
    PIDController pid(0.0, 0.0, 1.0, 1.0);
    pid.reset();

    // prime prev_error
    EXPECT_DOUBLE_EQ(pid.compute(0.0, 0.0), 0.0);
    // step change: derivative should produce kd * (1 - 0) / dt = 1
    EXPECT_DOUBLE_EQ(pid.compute(1.0, 0.0), 1.0);
}

/** @test Output limits cause clamping and anti-windup prevents growth */
TEST(PIDControllerTests, OutputLimitsAndAntiWindup) {
    PIDController pid(0.0, 1.0, 0.0, 1.0);
    pid.set_output_limits(-0.5, 0.5);

    EXPECT_DOUBLE_EQ(pid.compute(1.0, 0.0), 0.5);
    // subsequent calls should remain clamped due to anti-windup
    EXPECT_DOUBLE_EQ(pid.compute(1.0, 0.0), 0.5);
}
