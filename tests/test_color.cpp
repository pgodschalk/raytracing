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
