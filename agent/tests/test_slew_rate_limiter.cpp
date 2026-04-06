/**
 * @file test_slew_rate_limiter.cpp
 * @brief Unit tests validating slew-rate limiter behavior and constraints.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "slew_rate_limiter.hpp"

using ::testing::FloatEq;

/** @test Verifies first step initializes limiter state directly to target. */
TEST(SlewRateLimiterTests, FirstStepInitializesState) {
    SlewRateLimiter limiter(0.1f);

    EXPECT_THAT(limiter.step(1.5f), FloatEq(1.5f));
    EXPECT_THAT(limiter.value(), FloatEq(1.5f));
}

/** @test Verifies positive delta is limited to configured max step. */
TEST(SlewRateLimiterTests, PositiveDeltaIsLimited) {
    SlewRateLimiter limiter(0.2f);
    limiter.reset(0.0f);

    EXPECT_THAT(limiter.step(1.0f), FloatEq(0.2f));
    EXPECT_THAT(limiter.step(1.0f), FloatEq(0.4f));
}

/** @test Verifies negative delta is limited to configured max step. */
TEST(SlewRateLimiterTests, NegativeDeltaIsLimited) {
    SlewRateLimiter limiter(0.25f);
    limiter.reset(1.0f);

    EXPECT_THAT(limiter.step(0.0f), FloatEq(0.75f));
    EXPECT_THAT(limiter.step(0.0f), FloatEq(0.5f));
}

/** @test Verifies small deltas below limit reach target exactly in one step. */
TEST(SlewRateLimiterTests, SmallDeltaReachesTargetExactly) {
    SlewRateLimiter limiter(0.5f);
    limiter.reset(1.0f);

    EXPECT_THAT(limiter.step(1.2f), FloatEq(1.2f));
}
