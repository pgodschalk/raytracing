#include "raytracing/interval.h"
#include <cmath> // For std::isinf
#include <gtest/gtest.h>
#include <limits>

// Test the default constructor
TEST(IntervalTest, DefaultConstructor) {
  interval empty;
  EXPECT_DOUBLE_EQ(empty.min, std::numeric_limits<double>::infinity());
  EXPECT_DOUBLE_EQ(empty.max, -std::numeric_limits<double>::infinity());
}

// Test the parameterized constructor
TEST(IntervalTest, ParameterizedConstructor) {
  double a = 1.0;
  double b = 3.5;
  interval iv(a, b);
  EXPECT_DOUBLE_EQ(iv.min, a);
  EXPECT_DOUBLE_EQ(iv.max, b);
}

// Test the size() function
TEST(IntervalTest, Size) {
  // Test for empty interval
  interval empty;
  EXPECT_TRUE(std::isinf(empty.size()));
  EXPECT_LT(empty.size(), 0); // size should be -infinity

  // Test for universe interval
  interval universe = interval::universe;
  EXPECT_TRUE(std::isinf(universe.size()));
  EXPECT_GT(universe.size(), 0); // size should be +infinity

  // Test for a normal interval
  interval iv(2.0, 5.0);
  EXPECT_DOUBLE_EQ(iv.size(), 3.0);
}

// Test the contains() function
TEST(IntervalTest, Contains) {
  // Test for empty interval
  interval empty;
  EXPECT_FALSE(empty.contains(0.0));
  EXPECT_FALSE(empty.contains(std::numeric_limits<double>::infinity()));
  EXPECT_FALSE(empty.contains(-std::numeric_limits<double>::infinity()));

  // Test for universe interval
  EXPECT_TRUE(interval::universe.contains(0.0));
  EXPECT_TRUE(interval::universe.contains(1.0));
  EXPECT_TRUE(interval::universe.contains(-1.0));
  EXPECT_TRUE(
      interval::universe.contains(std::numeric_limits<double>::infinity()));
  EXPECT_TRUE(
      interval::universe.contains(-std::numeric_limits<double>::infinity()));

  // Test for a normal interval
  interval iv(1.0, 2.0);
  EXPECT_TRUE(iv.contains(1.0));  // Boundary case
  EXPECT_TRUE(iv.contains(1.5));  // Inside interval
  EXPECT_TRUE(iv.contains(2.0));  // Boundary case
  EXPECT_FALSE(iv.contains(0.5)); // Below interval
  EXPECT_FALSE(iv.contains(2.5)); // Above interval
}

// Test the surrounds() function
TEST(IntervalTest, Surrounds) {
  // Test for empty interval
  interval empty;
  EXPECT_FALSE(empty.surrounds(0.0));
  EXPECT_FALSE(empty.surrounds(std::numeric_limits<double>::infinity()));
  EXPECT_FALSE(empty.surrounds(-std::numeric_limits<double>::infinity()));

  // Test for universe interval
  EXPECT_TRUE(interval::universe.surrounds(0.0));
  EXPECT_TRUE(interval::universe.surrounds(1.0));
  EXPECT_TRUE(interval::universe.surrounds(-1.0));
  EXPECT_FALSE(
      interval::universe.surrounds(std::numeric_limits<double>::infinity()));
  EXPECT_FALSE(
      interval::universe.surrounds(-std::numeric_limits<double>::infinity()));

  // Test for a normal interval
  interval iv(1.0, 2.0);
  EXPECT_FALSE(iv.surrounds(1.0)); // Boundary case (not strict)
  EXPECT_TRUE(iv.surrounds(1.5));  // Inside interval
  EXPECT_FALSE(iv.surrounds(2.0)); // Boundary case (not strict)
  EXPECT_FALSE(iv.surrounds(0.5)); // Below interval
  EXPECT_FALSE(iv.surrounds(2.5)); // Above interval
}

// Test the clamp() function
TEST(IntervalTest, Clamp) {
  // Test for empty interval
  interval empty;
  EXPECT_DOUBLE_EQ(empty.clamp(0.0), std::numeric_limits<double>::infinity());
  EXPECT_DOUBLE_EQ(empty.clamp(-100.0),
                   std::numeric_limits<double>::infinity());

  // Test for universe interval
  EXPECT_DOUBLE_EQ(interval::universe.clamp(1.0), 1.0);
  EXPECT_DOUBLE_EQ(interval::universe.clamp(-1.0), -1.0);
  EXPECT_DOUBLE_EQ(
      interval::universe.clamp(std::numeric_limits<double>::infinity()),
      std::numeric_limits<double>::infinity());
  EXPECT_DOUBLE_EQ(
      interval::universe.clamp(-std::numeric_limits<double>::infinity()),
      -std::numeric_limits<double>::infinity());

  // Test for a normal interval
  interval iv(1.0, 2.0);
  EXPECT_DOUBLE_EQ(iv.clamp(0.5), 1.0); // Below min
  EXPECT_DOUBLE_EQ(iv.clamp(1.0), 1.0); // At min
  EXPECT_DOUBLE_EQ(iv.clamp(1.5), 1.5); // Inside interval
  EXPECT_DOUBLE_EQ(iv.clamp(2.0), 2.0); // At max
  EXPECT_DOUBLE_EQ(iv.clamp(2.5), 2.0); // Above max
}

// Test the static constants empty and universe
TEST(IntervalTest, StaticConstants) {
  // Test the empty interval
  EXPECT_DOUBLE_EQ(interval::empty.min,
                   std::numeric_limits<double>::infinity());
  EXPECT_DOUBLE_EQ(interval::empty.max,
                   -std::numeric_limits<double>::infinity());

  // Test the universe interval
  EXPECT_DOUBLE_EQ(interval::universe.min,
                   -std::numeric_limits<double>::infinity());
  EXPECT_DOUBLE_EQ(interval::universe.max,
                   std::numeric_limits<double>::infinity());
}
