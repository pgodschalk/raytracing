#include "raytracing/vec3.h"

#include <cmath>
#include <gtest/gtest.h>

// Helper function to compare two vec3 objects with a tolerance
bool vec3_approx_equal(const vec3 &v1, const vec3 &v2, double epsilon = 1e-10) {
  return std::abs(v1.x() - v2.x()) < epsilon &&
         std::abs(v1.y() - v2.y()) < epsilon &&
         std::abs(v1.z() - v2.z()) < epsilon;
}

// Constructor Tests
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

// Accessor and Operator[]
TEST(Vec3Test, Accessors) {
  vec3 v(4.0, 5.0, 6.0);
  EXPECT_DOUBLE_EQ(v.x(), 4.0);
  EXPECT_DOUBLE_EQ(v.y(), 5.0);
  EXPECT_DOUBLE_EQ(v.z(), 6.0);
  EXPECT_DOUBLE_EQ(v[0], 4.0);
  EXPECT_DOUBLE_EQ(v[1], 5.0);
  EXPECT_DOUBLE_EQ(v[2], 6.0);
}

TEST(Vec3Test, ModifierOperator) {
  vec3 v(1.0, 2.0, 3.0);
  v[0] = 7.0;
  v[1] = 8.0;
  v[2] = 9.0;
  EXPECT_DOUBLE_EQ(v.x(), 7.0);
  EXPECT_DOUBLE_EQ(v.y(), 8.0);
  EXPECT_DOUBLE_EQ(v.z(), 9.0);
}

// Unary Negation
TEST(Vec3Test, UnaryNegation) {
  vec3 v(1.0, -2.0, 3.0);
  vec3 neg_v = -v;
  EXPECT_DOUBLE_EQ(neg_v.x(), -1.0);
  EXPECT_DOUBLE_EQ(neg_v.y(), 2.0);
  EXPECT_DOUBLE_EQ(neg_v.z(), -3.0);
}

// Addition
TEST(Vec3Test, Addition) {
  vec3 u(1.0, 2.0, 3.0);
  vec3 v(4.0, 5.0, 6.0);
  vec3 sum = u + v;
  vec3 expected(5.0, 7.0, 9.0);
  EXPECT_TRUE(vec3_approx_equal(sum, expected));
}

// Subtraction
TEST(Vec3Test, Subtraction) {
  vec3 u(4.0, 5.0, 6.0);
  vec3 v(1.0, 2.0, 3.0);
  vec3 diff = u - v;
  vec3 expected(3.0, 3.0, 3.0);
  EXPECT_TRUE(vec3_approx_equal(diff, expected));
}

// Component-wise Multiplication
TEST(Vec3Test, ComponentWiseMultiplication) {
  vec3 u(2.0, 3.0, 4.0);
  vec3 v(5.0, 6.0, 7.0);
  vec3 prod = u * v;
  vec3 expected(10.0, 18.0, 28.0);
  EXPECT_TRUE(vec3_approx_equal(prod, expected));
}

// Scalar Multiplication
TEST(Vec3Test, ScalarMultiplication) {
  vec3 v(1.0, -2.0, 3.0);
  double scalar = 3.0;
  vec3 prod1 = scalar * v;
  vec3 prod2 = v * scalar;
  vec3 expected(3.0, -6.0, 9.0);
  EXPECT_TRUE(vec3_approx_equal(prod1, expected));
  EXPECT_TRUE(vec3_approx_equal(prod2, expected));
}

// Scalar Division
TEST(Vec3Test, ScalarDivision) {
  vec3 v(2.0, -4.0, 6.0);
  double scalar = 2.0;
  vec3 div = v / scalar;
  vec3 expected(1.0, -2.0, 3.0);
  EXPECT_TRUE(vec3_approx_equal(div, expected));
}

// Dot Product
TEST(Vec3Test, DotProduct) {
  vec3 u(1.0, 3.0, -5.0);
  vec3 v(4.0, -2.0, -1.0);
  double dot_prod = dot(u, v);
  EXPECT_DOUBLE_EQ(dot_prod,
                   (1.0 * 4.0 + 3.0 * (-2.0) + (-5.0) * (-1.0))); // 4 -6 +5 = 3
}

// Cross Product
TEST(Vec3Test, CrossProduct) {
  vec3 u(2.0, 3.0, 4.0);
  vec3 v(5.0, 6.0, 7.0);
  vec3 cross_prod = cross(u, v);
  vec3 expected(-3.0, 6.0, -3.0);
  EXPECT_TRUE(vec3_approx_equal(cross_prod, expected));
}

// Length and Length Squared
TEST(Vec3Test, LengthCalculations) {
  vec3 v(1.0, 2.0, 2.0);
  EXPECT_DOUBLE_EQ(v.length_squared(), 9.0);
  EXPECT_DOUBLE_EQ(v.length(), 3.0);
}

// Unit Vector
TEST(Vec3Test, UnitVector) {
  vec3 v(0.0, 3.0, 4.0);
  vec3 unit = unit_vector(v);
  vec3 expected(0.0, 0.6, 0.8);
  EXPECT_TRUE(vec3_approx_equal(unit, expected));
}

// Compound Assignment Operators
TEST(Vec3Test, CompoundAssignments) {
  vec3 v(1.0, 2.0, 3.0);
  vec3 u(4.0, 5.0, 6.0);

  v += u;
  vec3 expected_add(5.0, 7.0, 9.0);
  EXPECT_TRUE(vec3_approx_equal(v, expected_add));

  v *= 2.0;
  vec3 expected_mul(10.0, 14.0, 18.0);
  EXPECT_TRUE(vec3_approx_equal(v, expected_mul));

  v /= 2.0;
  vec3 expected_div(5.0, 7.0, 9.0);
  EXPECT_TRUE(vec3_approx_equal(v, expected_div));
}
