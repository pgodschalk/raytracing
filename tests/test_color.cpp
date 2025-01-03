#include "raytracing/color.h"

#include <gtest/gtest.h>
#include <sstream>

// Test case for black color
TEST(WriteColorTest, BlackColor) {
  vec3 black(0.0, 0.0, 0.0);
  std::stringstream ss;
  write_color(ss, black);
  EXPECT_EQ(ss.str(), "0 0 0\n");
}

// Test case for white color
TEST(WriteColorTest, WhiteColor) {
  vec3 white(1.0, 1.0, 1.0);
  std::stringstream ss;
  write_color(ss, white);
  EXPECT_EQ(ss.str(), "255 255 255\n");
}

// Test case for middle gray
TEST(WriteColorTest, MiddleGray) {
  vec3 gray(0.5, 0.5, 0.5);
  std::stringstream ss;
  write_color(ss, gray);
  // 255.999 * 0.5 = 127.9995 -> int casting truncates to 127
  EXPECT_EQ(ss.str(), "127 127 127\n");
}

// Test case for arbitrary color
TEST(WriteColorTest, ArbitraryColor) {
  vec3 color(0.25, 0.75, 0.5);
  std::stringstream ss;
  write_color(ss, color);
  EXPECT_EQ(ss.str(), "63 191 127\n"); // 255.999*0.25≈63.99975, etc.
}

// Test case for colors exceeding 1.0
TEST(WriteColorTest, ExceedingColors) {
  vec3 color(1.5, 2.0, 3.0);
  std::stringstream ss;
  write_color(ss, color);
  EXPECT_EQ(ss.str(), "383 511 767\n"); // No clamping applied
}

// Test case for negative colors
TEST(WriteColorTest, NegativeColors) {
  vec3 color(-0.1, -0.5, -1.0);
  std::stringstream ss;
  write_color(ss, color);
  EXPECT_EQ(ss.str(), "-25 -127 -255\n"); // Negative values handled by casting
}

// Test case for edge values
TEST(WriteColorTest, EdgeValues) {
  vec3 color(0.0, 1.0, 0.999);
  std::stringstream ss;
  write_color(ss, color);
  EXPECT_EQ(ss.str(),
            "0 255 255\n"); // 255.999 * 0.999 ≈ 255.743, truncates to 255
}
