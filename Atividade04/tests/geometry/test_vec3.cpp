#include <gtest/gtest.h>
#include "geometry/vec3.h"

TEST(Vec3Test, DefaultConstructor) {
    vec3 v;
    EXPECT_EQ(v.x(), 0.0);
    EXPECT_EQ(v.y(), 0.0);
    EXPECT_EQ(v.z(), 0.0);
}

TEST(Vec3Test, CustomConstructor) {
    vec3 v(1.0, 2.0, 3.0);
    EXPECT_EQ(v.x(), 1.0);
    EXPECT_EQ(v.y(), 2.0);
    EXPECT_EQ(v.z(), 3.0);
}

TEST(Vec3Test, NegationOperator) {
    vec3 v(1.0, 2.0, 3.0);
    vec3 result = -v;
    EXPECT_EQ(result.x(), -1.0);
    EXPECT_EQ(result.y(), -2.0);
    EXPECT_EQ(result.z(), -3.0);
}

TEST(Vec3Test, AdditionOperator) {
    vec3 u(1.0, 2.0, 3.0);
    vec3 v(4.0, 5.0, 6.0);
    vec3 result = u + v;
    EXPECT_EQ(result.x(), 5.0);
    EXPECT_EQ(result.y(), 7.0);
    EXPECT_EQ(result.z(), 9.0);
}

TEST(Vec3Test, SubtractionOperator) {
    vec3 u(4.0, 5.0, 6.0);
    vec3 v(1.0, 2.0, 3.0);
    vec3 result = u - v;
    EXPECT_EQ(result.x(), 3.0);
    EXPECT_EQ(result.y(), 3.0);
    EXPECT_EQ(result.z(), 3.0);
}

TEST(Vec3Test, MultiplicationOperator) {
    vec3 v(2.0, 3.0, 4.0);
    vec3 result = v * 2.0;
    EXPECT_EQ(result.x(), 4.0);
    EXPECT_EQ(result.y(), 6.0);
    EXPECT_EQ(result.z(), 8.0);
}

TEST(Vec3Test, DivisionOperator) {
    vec3 v(4.0, 6.0, 8.0);
    vec3 result = v / 2.0;
    EXPECT_EQ(result.x(), 2.0);
    EXPECT_EQ(result.y(), 3.0);
    EXPECT_EQ(result.z(), 4.0);
}

TEST(Vec3Test, Length) {
    vec3 v(1.0, 2.0, 2.0);
    EXPECT_DOUBLE_EQ(v.length(), 3.0);
}

TEST(Vec3Test, LengthSquared) {
    vec3 v(1.0, 2.0, 2.0);
    EXPECT_DOUBLE_EQ(v.length_squared(), 9.0);
}

TEST(Vec3Test, DotProduct) {
    vec3 u(1.0, 2.0, 3.0);
    vec3 v(4.0, 5.0, 6.0);
    EXPECT_DOUBLE_EQ(dot(u, v), 32.0);
}

TEST(Vec3Test, CrossProduct) {
    vec3 u(1.0, 2.0, 3.0);
    vec3 v(4.0, 5.0, 6.0);
    vec3 result = cross(u, v);
    EXPECT_EQ(result.x(), -3.0);
    EXPECT_EQ(result.y(), 6.0);
    EXPECT_EQ(result.z(), -3.0);
}

TEST(Vec3Test, UnitVector) {
    vec3 v(1.0, 2.0, 2.0);
    vec3 unit_v = unit_vector(v);
    EXPECT_DOUBLE_EQ(unit_v.length(), 1.0);
    EXPECT_DOUBLE_EQ(unit_v.x(), 1.0 / 3.0);
    EXPECT_DOUBLE_EQ(unit_v.y(), 2.0 / 3.0);
    EXPECT_DOUBLE_EQ(unit_v.z(), 2.0 / 3.0);
}