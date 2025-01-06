#include "raytracing/rtweekend.h"
#include "raytracing/vec3.h"
#include <gtest/gtest.h>
#include <limits>

// Test the defined constants
TEST(RTWeekendTest, Constants) {
  // Test infinity
  EXPECT_EQ(infinity, std::numeric_limits<double>::infinity());

  // Test pi with a tolerance
  EXPECT_NEAR(pi, 3.1415926535897932385, 1e-15);
}

// Test the degrees_to_radians function
TEST(RTWeekendTest, DegreesToRadians) {
  // 0 degrees
  EXPECT_DOUBLE_EQ(degrees_to_radians(0.0), 0.0);

  // 90 degrees
  EXPECT_DOUBLE_EQ(degrees_to_radians(90.0), pi / 2);

  // 180 degrees
  EXPECT_DOUBLE_EQ(degrees_to_radians(180.0), pi);

  // 360 degrees
  EXPECT_DOUBLE_EQ(degrees_to_radians(360.0), 2 * pi);

  // Negative degrees
  EXPECT_DOUBLE_EQ(degrees_to_radians(-45.0), -pi / 4);

  // Non-integer degrees
  EXPECT_NEAR(degrees_to_radians(45.0), pi / 4, 1e-15);
  EXPECT_NEAR(degrees_to_radians(30.0), pi / 6, 1e-15);
}

// Ttest shared_ptr and make_shared usage
TEST(RTWeekendTest, SharedPointerUsage) {
  // Example with vec3 (assuming vec3 has a default constructor)
  shared_ptr<vec3> ptr = make_shared<vec3>();
  EXPECT_NE(ptr, nullptr);
}
