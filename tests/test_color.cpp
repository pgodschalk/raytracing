#include "raytracing/color.h"
#include "gtest/gtest.h"
#include <sstream>

// Tests for the linear_to_gamma function
TEST(ColorTest, LinearToGammaPositive) {
  EXPECT_DOUBLE_EQ(linear_to_gamma(1.0), 1.0);
  EXPECT_DOUBLE_EQ(linear_to_gamma(0.25), 0.5);
  EXPECT_DOUBLE_EQ(linear_to_gamma(0.81), 0.9);
}

TEST(ColorTest, LinearToGammaZeroAndNegative) {
  EXPECT_DOUBLE_EQ(linear_to_gamma(0.0), 0.0);
  EXPECT_DOUBLE_EQ(linear_to_gamma(-1.0), 0.0);
  EXPECT_DOUBLE_EQ(linear_to_gamma(-0.5), 0.0);
}

TEST(ColorTest, LinearToGammaFractionalValues) {
  EXPECT_DOUBLE_EQ(linear_to_gamma(0.04), 0.2);
  EXPECT_DOUBLE_EQ(linear_to_gamma(0.64), 0.8);
}

// Tests for the write_color function
TEST(ColorTest, WriteColorNormalValues) {
  color c(0.25, 0.5, 0.75); // After gamma: 0.5, ~0.7071, ~0.8660
  std::stringstream ss;
  write_color(ss, c);

  // Expected byte values:
  // r: sqrt(0.25) = 0.5 * 256 = 128
  // g: sqrt(0.5) ≈ 0.7071 * 256 ≈ 181
  // b: sqrt(0.75) ≈ 0.8660 * 256 ≈ 221
  EXPECT_EQ(ss.str(), "128 181 221\n");
}

TEST(ColorTest, WriteColorClampHighValues) {
  color c(1.5, 2.0, 0.999); // After gamma: >1.0, >1.0, ~0.9995
  std::stringstream ss;
  write_color(ss, c);

  // Expected byte values after clamping:
  // r: clamp(sqrt(1.5)) => clamp(1.2247) => 0.999 * 256 ≈ 255
  // g: clamp(sqrt(2.0)) => clamp(1.4142) => 0.999 * 256 ≈ 255
  // b: clamp(sqrt(0.999)) => clamp(~0.9995) => 0.999 * 256 ≈ 255
  EXPECT_EQ(ss.str(), "255 255 255\n");
}

TEST(ColorTest, WriteColorClampLowValues) {
  color c(-0.5, 0.0, 0.1); // After gamma: 0, 0, ~0.3162
  std::stringstream ss;
  write_color(ss, c);

  // Expected byte values after clamping:
  // r: clamp(-0.5) => 0 * 256 = 0
  // g: clamp(0.0) => 0 * 256 = 0
  // b: clamp(sqrt(0.1)) ≈ 0.3162 * 256 ≈ 80.8 => 80
  EXPECT_EQ(ss.str(), "0 0 80\n");
}

TEST(ColorTest, WriteColorEdgeCases) {
  // Test maximum clamped value
  color c(0.999, 0.999, 0.999);
  std::stringstream ss1;
  write_color(ss1, c);
  EXPECT_EQ(ss1.str(), "255 255 255\n");

  // Test minimum clamped value
  color c_min(0.0, 0.0, 0.0);
  std::stringstream ss2;
  write_color(ss2, c_min);
  EXPECT_EQ(ss2.str(), "0 0 0\n");
}

TEST(ColorTest, WriteColorRounding) {
  // Values that when multiplied by 256 are not integers
  color c(0.00390625, 0.5, 0.99609375); // 1/256, 0.5, 255/256
  std::stringstream ss;
  write_color(ss, c);

  // Expected byte values:
  // r: sqrt(0.00390625) = 0.0625 * 256 = 16
  // g: sqrt(0.5) ≈ 0.7071 * 256 ≈ 181
  // b: clamp(sqrt(0.99609375)) ≈ clamp(0.998046875) => 0.998046875 * 256 ≈
  // 255.0
  EXPECT_EQ(ss.str(), "16 181 255\n");
}
