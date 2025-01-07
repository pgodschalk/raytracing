#include "raytracing/ray.h"
#include "raytracing/vec3.h"
#include <gtest/gtest.h>

TEST(RayTest, DefaultConstructor) {
  ray r;
  // Assuming the default constructors for point3 and vec3 default to (0,0,0)
  EXPECT_EQ(r.origin().x(), 0.0);
  EXPECT_EQ(r.origin().y(), 0.0);
  EXPECT_EQ(r.origin().z(), 0.0);

  EXPECT_EQ(r.direction().x(), 0.0);
  EXPECT_EQ(r.direction().y(), 0.0);
  EXPECT_EQ(r.direction().z(), 0.0);
}

TEST(RayTest, ParameterizedConstructor) {
  point3 orig(1.0, 2.0, 3.0);
  vec3 dir(4.0, 5.0, 6.0);
  ray r(orig, dir);

  EXPECT_EQ(r.origin().x(), 1.0);
  EXPECT_EQ(r.origin().y(), 2.0);
  EXPECT_EQ(r.origin().z(), 3.0);

  EXPECT_EQ(r.direction().x(), 4.0);
  EXPECT_EQ(r.direction().y(), 5.0);
  EXPECT_EQ(r.direction().z(), 6.0);
}

TEST(RayTest, AtMethod) {
  point3 orig(1.0, 2.0, 3.0);
  vec3 dir(4.0, 5.0, 6.0);
  ray r(orig, dir);

  double t = 2.0;
  point3 result = r.at(t);

  // Expected: orig + t * dir = (1 + 2*4, 2 + 2*5, 3 + 2*6)
  EXPECT_EQ(result.x(), 9.0);  // 1 + 8
  EXPECT_EQ(result.y(), 12.0); // 2 + 10
  EXPECT_EQ(result.z(), 15.0); // 3 + 12
}
