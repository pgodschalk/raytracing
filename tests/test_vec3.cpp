#include "raytracing/vec3.h"
#include <cmath>
#include <gtest/gtest.h>

TEST(Vec3Test, DefaultConstructor) {
  vec3 v;
  EXPECT_DOUBLE_EQ(v.x(), 0.0);
  EXPECT_DOUBLE_EQ(v.y(), 0.0);
  EXPECT_DOUBLE_EQ(v.z(), 0.0);
}

TEST(Vec3Test, ParameterizedConstructor) {
  vec3 v(1.0, 2.0, 3.0);
  EXPECT_DOUBLE_EQ(v.x(), 1.0);
  EXPECT_DOUBLE_EQ(v.y(), 2.0);
  EXPECT_DOUBLE_EQ(v.z(), 3.0);
}

TEST(Vec3Test, NegationOperator) {
  vec3 v(1.0, -2.0, 3.0);
  vec3 negV = -v;
  EXPECT_DOUBLE_EQ(negV.x(), -1.0);
  EXPECT_DOUBLE_EQ(negV.y(), 2.0);
  EXPECT_DOUBLE_EQ(negV.z(), -3.0);
}

TEST(Vec3Test, AdditionAssignmentOperator) {
  vec3 v1(1.0, 2.0, 3.0);
  vec3 v2(2.0, 2.0, 2.0);
  v1 += v2;
  EXPECT_DOUBLE_EQ(v1.x(), 3.0);
  EXPECT_DOUBLE_EQ(v1.y(), 4.0);
  EXPECT_DOUBLE_EQ(v1.z(), 5.0);
}

TEST(Vec3Test, MultiplyAssignmentOperator) {
  vec3 v(1.0, 2.0, 3.0);
  v *= 2.0;
  EXPECT_DOUBLE_EQ(v.x(), 2.0);
  EXPECT_DOUBLE_EQ(v.y(), 4.0);
  EXPECT_DOUBLE_EQ(v.z(), 6.0);
}

TEST(Vec3Test, DivideAssignmentOperator) {
  vec3 v(2.0, 4.0, 6.0);
  v /= 2.0;
  EXPECT_DOUBLE_EQ(v.x(), 1.0);
  EXPECT_DOUBLE_EQ(v.y(), 2.0);
  EXPECT_DOUBLE_EQ(v.z(), 3.0);
}

TEST(Vec3Test, Length) {
  vec3 v(1.0, 2.0, 2.0);
  EXPECT_DOUBLE_EQ(v.length(), 3.0);
}

TEST(Vec3Test, LengthSquared) {
  vec3 v(1.0, 2.0, 2.0);
  EXPECT_DOUBLE_EQ(v.length_squared(), 9.0);
}

TEST(Vec3Test, AdditionOperator) {
  vec3 v1(1.0, 2.0, 3.0);
  vec3 v2(2.0, 3.0, 4.0);
  vec3 result = v1 + v2;
  EXPECT_DOUBLE_EQ(result.x(), 3.0);
  EXPECT_DOUBLE_EQ(result.y(), 5.0);
  EXPECT_DOUBLE_EQ(result.z(), 7.0);
}

TEST(Vec3Test, SubtractionOperator) {
  vec3 v1(1.0, 2.0, 3.0);
  vec3 v2(2.0, 3.0, 4.0);
  vec3 result = v1 - v2;
  EXPECT_DOUBLE_EQ(result.x(), -1.0);
  EXPECT_DOUBLE_EQ(result.y(), -1.0);
  EXPECT_DOUBLE_EQ(result.z(), -1.0);
}

TEST(Vec3Test, MultiplicationOperatorVec3) {
  vec3 v1(1.0, 2.0, 3.0);
  vec3 v2(2.0, 3.0, 4.0);
  vec3 result = v1 * v2;
  EXPECT_DOUBLE_EQ(result.x(), 2.0);
  EXPECT_DOUBLE_EQ(result.y(), 6.0);
  EXPECT_DOUBLE_EQ(result.z(), 12.0);
}

TEST(Vec3Test, MultiplicationOperatorScalar) {
  vec3 v(1.0, 2.0, 3.0);
  vec3 result1 = 2.0 * v;
  vec3 result2 = v * 3.0;
  EXPECT_DOUBLE_EQ(result1.x(), 2.0);
  EXPECT_DOUBLE_EQ(result1.y(), 4.0);
  EXPECT_DOUBLE_EQ(result1.z(), 6.0);
  EXPECT_DOUBLE_EQ(result2.x(), 3.0);
  EXPECT_DOUBLE_EQ(result2.y(), 6.0);
  EXPECT_DOUBLE_EQ(result2.z(), 9.0);
}

TEST(Vec3Test, DivisionOperatorScalar) {
  vec3 v(2.0, 4.0, 6.0);
  vec3 result = v / 2.0;
  EXPECT_DOUBLE_EQ(result.x(), 1.0);
  EXPECT_DOUBLE_EQ(result.y(), 2.0);
  EXPECT_DOUBLE_EQ(result.z(), 3.0);
}

TEST(Vec3Test, DotProduct) {
  vec3 v1(1.0, 2.0, 3.0);
  vec3 v2(4.0, -5.0, 6.0);
  double result = dot(v1, v2);
  EXPECT_DOUBLE_EQ(result, (1.0 * 4.0) + (2.0 * -5.0) + (3.0 * 6.0));
  EXPECT_DOUBLE_EQ(result, 4.0 - 10.0 + 18.0);
}

TEST(Vec3Test, CrossProduct) {
  vec3 v1(1.0, 2.0, 3.0);
  vec3 v2(2.0, 3.0, 4.0);
  vec3 result = cross(v1, v2);
  // cross(1,2,3),(2,3,4) = (2*4 - 3*3, 3*2 - 1*4, 1*3 - 2*2)
  //                      = (8 - 9, 6 - 4, 3 - 4) = (-1, 2, -1)
  EXPECT_DOUBLE_EQ(result.x(), -1.0);
  EXPECT_DOUBLE_EQ(result.y(), 2.0);
  EXPECT_DOUBLE_EQ(result.z(), -1.0);
}

TEST(Vec3Test, UnitVector) {
  vec3 v(1.0, 2.0, 2.0);
  vec3 unitV = unit_vector(v);
  double len = std::sqrt(1.0 + 4.0 + 4.0); // 3.0
  EXPECT_DOUBLE_EQ(unitV.x(), 1.0 / len);
  EXPECT_DOUBLE_EQ(unitV.y(), 2.0 / len);
  EXPECT_DOUBLE_EQ(unitV.z(), 2.0 / len);
}
