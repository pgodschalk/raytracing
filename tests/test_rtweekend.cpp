#include "raytracing/rtweekend.h"
#include <cmath>
#include <gtest/gtest.h>

TEST(RTWeekendTest, InfinityValue) {
  EXPECT_TRUE(std::isinf(infinity))
      << "Expected infinity to be an infinite value.";
}

TEST(RTWeekendTest, PiValue) {
  // Check that our declared 'pi' matches an expected double approximation.
  EXPECT_NEAR(pi, 3.141592653589793, 1e-15)
      << "Expected pi to be approximately 3.141592653589793.";
}

TEST(RTWeekendTest, DegreesToRadiansZero) {
  EXPECT_NEAR(degrees_to_radians(0.0), 0.0, 1e-15)
      << "Expected 0 degrees to convert to 0 radians.";
}

TEST(RTWeekendTest, DegreesToRadiansHalfCircle) {
  EXPECT_NEAR(degrees_to_radians(180.0), pi, 1e-15)
      << "Expected 180 degrees to convert to pi radians.";
}

TEST(RTWeekendTest, DegreesToRadiansFullCircle) {
  EXPECT_NEAR(degrees_to_radians(360.0), 2 * pi, 1e-15)
      << "Expected 360 degrees to convert to 2*pi radians.";
}
