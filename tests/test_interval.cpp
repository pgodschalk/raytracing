#include "raytracing/interval.h"
#include "raytracing/rtweekend.h"
#include <gtest/gtest.h>

TEST(IntervalTest, DefaultConstructor) {
  interval i;
  EXPECT_EQ(i.min, +infinity);
  EXPECT_EQ(i.max, -infinity);
}

TEST(IntervalTest, ConstructorWithValues) {
  interval i(1.0, 5.0);
  EXPECT_EQ(i.min, 1.0);
  EXPECT_EQ(i.max, 5.0);
}

TEST(IntervalTest, Size) {
  interval i(1.0, 5.0);
  EXPECT_DOUBLE_EQ(i.size(), 4.0);
}

TEST(IntervalTest, Contains) {
  interval i(1.0, 5.0);
  EXPECT_TRUE(i.contains(1.0));
  EXPECT_TRUE(i.contains(3.0));
  EXPECT_TRUE(i.contains(5.0));
  EXPECT_FALSE(i.contains(0.9));
  EXPECT_FALSE(i.contains(5.1));
}

TEST(IntervalTest, Surrounds) {
  interval i(1.0, 5.0);
  EXPECT_FALSE(i.surrounds(1.0));
  EXPECT_TRUE(i.surrounds(3.0));
  EXPECT_FALSE(i.surrounds(5.0));
  EXPECT_FALSE(i.surrounds(0.9));
  EXPECT_FALSE(i.surrounds(5.1));
}

TEST(IntervalTest, Clamp) {
  interval i(1.0, 5.0);
  EXPECT_DOUBLE_EQ(i.clamp(3.0), 3.0);
  EXPECT_DOUBLE_EQ(i.clamp(0.0), 1.0);
  EXPECT_DOUBLE_EQ(i.clamp(6.0), 5.0);
}

TEST(IntervalTest, StaticMembers) {
  EXPECT_EQ(interval::empty.min, +infinity);
  EXPECT_EQ(interval::empty.max, -infinity);

  EXPECT_EQ(interval::universe.min, -infinity);
  EXPECT_EQ(interval::universe.max, +infinity);
}
