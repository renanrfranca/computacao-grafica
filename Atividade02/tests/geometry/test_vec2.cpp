#include <gtest/gtest.h>
#include "geometry/vec2.h"

TEST(Vec2Test, DefaultConstructor) {
    vec2 v;
    EXPECT_EQ(v.x(), 0.0);
    EXPECT_EQ(v.y(), 0.0);
}

TEST(Vec2Test, CustomConstructor) {
    vec2 v(1.0, 2.0);
    EXPECT_EQ(v.x(), 1.0);
    EXPECT_EQ(v.y(), 2.0);
}

TEST(Vec2Test, NegationOperator) {
    vec2 v(1.0, 2.0);
    vec2 result = -v;
    EXPECT_EQ(result.x(), -1.0);
    EXPECT_EQ(result.y(), -2.0);
}

TEST(Vec2Test, AdditionOperator) {
    vec2 u(1.0, 2.0);
    vec2 v(3.0, 4.0);
    vec2 result = u + v;
    EXPECT_EQ(result.x(), 4.0);
    EXPECT_EQ(result.y(), 6.0);
}

TEST(Vec2Test, SubtractionOperator) {
    vec2 u(3.0, 5.0);
    vec2 v(1.0, 2.0);
    vec2 result = u - v;
    EXPECT_EQ(result.x(), 2.0);
    EXPECT_EQ(result.y(), 3.0);
}

TEST(Vec2Test, MultiplicationOperator) {
    vec2 v(2.0, 3.0);
    vec2 result = v * 2.0;
    EXPECT_EQ(result.x(), 4.0);
    EXPECT_EQ(result.y(), 6.0);
}

TEST(Vec2Test, DivisionOperator) {
    vec2 v(4.0, 6.0);
    vec2 result = v / 2.0;
    EXPECT_EQ(result.x(), 2.0);
    EXPECT_EQ(result.y(), 3.0);
}

TEST(Vec2Test, Length) {
    vec2 v(3.0, 4.0);  // 3-4-5 right triangle
    EXPECT_EQ(v.length(), 5.0);
}

TEST(Vec2Test, LengthSquared) {
    vec2 v(3.0, 4.0);
    EXPECT_EQ(v.length_squared(), 25.0);
}

TEST(Vec2Test, DotProduct) {
    vec2 u(1.0, 2.0);
    vec2 v(3.0, 4.0);
    EXPECT_EQ(dot(u, v), 11.0);
}

TEST(Vec2Test, CrossProduct) {
    vec2 u(1.0, 2.0);
    vec2 v(3.0, 4.0);
    EXPECT_EQ(cross(u, v), -2.0);
}

TEST(Vec2Test, UnitVector) {
    vec2 v(3.0, 4.0);
    vec2 unit_v = unit_vector(v);
    EXPECT_DOUBLE_EQ(unit_v.length(), 1.0);
    EXPECT_DOUBLE_EQ(unit_v.x(), 3.0 / 5.0);
    EXPECT_DOUBLE_EQ(unit_v.y(), 4.0 / 5.0);
}