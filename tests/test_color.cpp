#include "raytracing/color.h"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Helper function to compare expected and actual output
void ExpectWriteColor(const color &pixel_color,
                      const std::string &expected_output) {
  std::ostringstream out;
  write_color(out, pixel_color);
  EXPECT_EQ(out.str(), expected_output);
}

TEST(ColorTest, BlackColorWritesCorrectly) {
  color black(0.0, 0.0, 0.0);
  ExpectWriteColor(black, "0 0 0\n");
}

TEST(ColorTest, WhiteColorWritesCorrectly) {
  color white(1.0, 1.0, 1.0);
  ExpectWriteColor(white, "255 255 255\n");
}

TEST(ColorTest, MidGrayColorWritesCorrectly) {
  color gray(0.5, 0.5, 0.5);
  ExpectWriteColor(gray, "128 128 128\n");
}

TEST(ColorTest, BoundaryColorWritesCorrectly_JustBelowOne) {
  color near_max(0.999, 0.999, 0.999);
  ExpectWriteColor(near_max, "255 255 255\n");
}

TEST(ColorTest, BoundaryColorWritesCorrectly_JustAboveZero) {
  color near_min(0.001, 0.001, 0.001);
  ExpectWriteColor(near_min, "0 0 0\n");
}

TEST(ColorTest, MixedColorWritesCorrectly) {
  color mixed(0.1, 0.5, 0.9);
  // int(255.999 * 0.1) = 25.5999 -> 25
  // int(255.999 * 0.5) = 127.9995 -> 127
  // int(255.999 * 0.9) = 230.3991 -> 230
  ExpectWriteColor(mixed, "25 128 230\n");
}
