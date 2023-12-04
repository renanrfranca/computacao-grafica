#include <gtest/gtest.h>
#include "geometry/vec4.h"

TEST(Vec4Test, DefaultConstructor) {
    vec4 v;
    EXPECT_EQ(v.x(), 0.0);
    EXPECT_EQ(v.y(), 0.0);
    EXPECT_EQ(v.z(), 0.0);
    EXPECT_EQ(v.w(), 0.0);
}

TEST(Vec4Test, CustomConstructor) {
    vec4 v(1.0, 2.0, 3.0, 4.0);
    EXPECT_EQ(v.x(), 1.0);
    EXPECT_EQ(v.y(), 2.0);
    EXPECT_EQ(v.z(), 3.0);
    EXPECT_EQ(v.w(), 4.0);
}

TEST(Vec4Test, NegationOperator) {
    vec4 v(1.0, 2.0, 3.0, 4.0);
    vec4 result = -v;
    EXPECT_EQ(result.x(), -1.0);
    EXPECT_EQ(result.y(), -2.0);
    EXPECT_EQ(result.z(), -3.0);
    EXPECT_EQ(result.w(), -4.0);
}

TEST(Vec4Test, AdditionOperator) {
    vec4 u(1.0, 2.0, 3.0, 4.0);
    vec4 v(5.0, 6.0, 7.0, 8.0);
    vec4 result = u + v;
    EXPECT_EQ(result.x(), 6.0);
    EXPECT_EQ(result.y(), 8.0);
    EXPECT_EQ(result.z(), 10.0);
    EXPECT_EQ(result.w(), 12.0);
}

TEST(Vec4Test, SubtractionOperator) {
    vec4 u(5.0, 6.0, 7.0, 8.0);
    vec4 v(1.0, 2.0, 3.0, 4.0);
    vec4 result = u - v;
    EXPECT_EQ(result.x(), 4.0);
    EXPECT_EQ(result.y(), 4.0);
    EXPECT_EQ(result.z(), 4.0);
    EXPECT_EQ(result.w(), 4.0);
}

TEST(Vec4Test, MultiplicationOperator) {
    vec4 v(2.0, 3.0, 4.0, 5.0);
    vec4 result = v * 2.0;
    EXPECT_EQ(result.x(), 4.0);
    EXPECT_EQ(result.y(), 6.0);
    EXPECT_EQ(result.z(), 8.0);
    EXPECT_EQ(result.w(), 10.0);
}

TEST(Vec4Test, DivisionOperator) {
    vec4 v(4.0, 6.0, 8.0, 10.0);
    vec4 result = v / 2.0;
    EXPECT_EQ(result.x(), 2.0);
    EXPECT_EQ(result.y(), 3.0);
    EXPECT_EQ(result.z(), 4.0);
    EXPECT_EQ(result.w(), 5.0);
}

TEST(Vec4Test, Length) {
    vec4 v(1.0, 2.0, 2.0, 3.0);  // 1-2-2-3 Pythagorean quadruple
    EXPECT_DOUBLE_EQ(v.length(), sqrt(18.0));
}

TEST(Vec4Test, LengthSquared) {
    vec4 v(1.0, 2.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v.length_squared(), 18.0);
}

TEST(Vec4Test, DotProduct) {
    vec4 u(1.0, 2.0, 3.0, 4.0);
    vec4 v(5.0, 6.0, 7.0, 8.0);
    EXPECT_DOUBLE_EQ(dot(u, v), 70.0);
}

TEST(Vec4Test, UnitVector) {
    vec4 v(1.0, 2.0, 2.0, 3.0);
    vec4 unit_v = unit_vector(v);
    EXPECT_DOUBLE_EQ(unit_v.length(), 1.0);
    EXPECT_DOUBLE_EQ(unit_v.x(), 1.0 / sqrt(18.0));
    EXPECT_DOUBLE_EQ(unit_v.y(), 2.0 / sqrt(18.0));
    EXPECT_DOUBLE_EQ(unit_v.z(), 2.0 / sqrt(18.0));
    EXPECT_DOUBLE_EQ(unit_v.w(), 3.0 / sqrt(18.0));
}