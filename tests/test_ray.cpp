#include "raytracing/ray.h"

#include "gtest/gtest.h"

// Test the default constructor
TEST(RayTest, DefaultConstructor) {
  ray r;
  // Assuming that point3 and vec3 default to (0,0,0)
  EXPECT_DOUBLE_EQ(r.origin().x(), 0.0);
  EXPECT_DOUBLE_EQ(r.origin().y(), 0.0);
  EXPECT_DOUBLE_EQ(r.origin().z(), 0.0);
  EXPECT_DOUBLE_EQ(r.direction().x(), 0.0);
  EXPECT_DOUBLE_EQ(r.direction().y(), 0.0);
  EXPECT_DOUBLE_EQ(r.direction().z(), 0.0);
}

// Test the parameterized constructor
TEST(RayTest, ParameterizedConstructor) {
  point3 origin(1.0, 2.0, 3.0);
  vec3 direction(4.0, 5.0, 6.0);
  ray r(origin, direction);

  EXPECT_DOUBLE_EQ(r.origin().x(), 1.0);
  EXPECT_DOUBLE_EQ(r.origin().y(), 2.0);
  EXPECT_DOUBLE_EQ(r.origin().z(), 3.0);
  EXPECT_DOUBLE_EQ(r.direction().x(), 4.0);
  EXPECT_DOUBLE_EQ(r.direction().y(), 5.0);
  EXPECT_DOUBLE_EQ(r.direction().z(), 6.0);
}

// Test the origin accessor
TEST(RayTest, OriginAccessor) {
  point3 origin(7.0, 8.0, 9.0);
  vec3 direction(10.0, 11.0, 12.0);
  ray r(origin, direction);

  const point3 &orig = r.origin();
  EXPECT_DOUBLE_EQ(orig.x(), 7.0);
  EXPECT_DOUBLE_EQ(orig.y(), 8.0);
  EXPECT_DOUBLE_EQ(orig.z(), 9.0);
}

// Test the direction accessor
TEST(RayTest, DirectionAccessor) {
  point3 origin(13.0, 14.0, 15.0);
  vec3 direction(16.0, 17.0, 18.0);
  ray r(origin, direction);

  const vec3 &dir = r.direction();
  EXPECT_DOUBLE_EQ(dir.x(), 16.0);
  EXPECT_DOUBLE_EQ(dir.y(), 17.0);
  EXPECT_DOUBLE_EQ(dir.z(), 18.0);
}

// Test the at(t) method with t = 0
TEST(RayTest, AtMethodZero) {
  point3 origin(0.0, 0.0, 0.0);
  vec3 direction(1.0, 1.0, 1.0);
  ray r(origin, direction);

  point3 p = r.at(0.0);
  EXPECT_DOUBLE_EQ(p.x(), 0.0);
  EXPECT_DOUBLE_EQ(p.y(), 0.0);
  EXPECT_DOUBLE_EQ(p.z(), 0.0);
}

// Test the at(t) method with t = 1
TEST(RayTest, AtMethodOne) {
  point3 origin(1.0, 2.0, 3.0);
  vec3 direction(4.0, 5.0, 6.0);
  ray r(origin, direction);

  point3 p = r.at(1.0);
  EXPECT_DOUBLE_EQ(p.x(), 5.0); // 1 + 4*1
  EXPECT_DOUBLE_EQ(p.y(), 7.0); // 2 + 5*1
  EXPECT_DOUBLE_EQ(p.z(), 9.0); // 3 + 6*1
}

// Test the at(t) method with t = 0.5
TEST(RayTest, AtMethodHalf) {
  point3 origin(2.0, 4.0, 6.0);
  vec3 direction(1.0, 1.0, 1.0);
  ray r(origin, direction);

  point3 p = r.at(0.5);
  EXPECT_DOUBLE_EQ(p.x(), 2.5); // 2 + 1*0.5
  EXPECT_DOUBLE_EQ(p.y(), 4.5); // 4 + 1*0.5
  EXPECT_DOUBLE_EQ(p.z(), 6.5); // 6 + 1*0.5
}

// Test the at(t) method with negative t
TEST(RayTest, AtMethodNegativeT) {
  point3 origin(3.0, 3.0, 3.0);
  vec3 direction(1.0, 2.0, 3.0);
  ray r(origin, direction);

  point3 p = r.at(-1.0);
  EXPECT_DOUBLE_EQ(p.x(), 2.0); // 3 + 1*(-1)
  EXPECT_DOUBLE_EQ(p.y(), 1.0); // 3 + 2*(-1)
  EXPECT_DOUBLE_EQ(p.z(), 0.0); // 3 + 3*(-1)
}
