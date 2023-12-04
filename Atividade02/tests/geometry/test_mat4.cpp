#include <gtest/gtest.h>
#include "geometry/mat4.h"

TEST(Mat4Test, DefaultConstructor) {
    mat4 m;
    EXPECT_EQ(m[0], vec4(1.0, 0.0, 0.0, 0.0));
    EXPECT_EQ(m[1], vec4(0.0, 1.0, 0.0, 0.0));
    EXPECT_EQ(m[2], vec4(0.0, 0.0, 1.0, 0.0));
    EXPECT_EQ(m[3], vec4(0.0, 0.0, 0.0, 1.0));
}

TEST(Mat4Test, CustomConstructor) {
    vec4 row1(1.0, 2.0, 3.0, 4.0);
    vec4 row2(5.0, 6.0, 7.0, 8.0);
    vec4 row3(9.0, 10.0, 11.0, 12.0);
    vec4 row4(13.0, 14.0, 15.0, 16.0);

    mat4 m(row1, row2, row3, row4);
    EXPECT_EQ(m[0], row1);
    EXPECT_EQ(m[1], row2);
    EXPECT_EQ(m[2], row3);
    EXPECT_EQ(m[3], row4);
}

TEST(Mat4Test, IndexOperator) {
    vec4 row1(1.0, 2.0, 3.0, 4.0);
    vec4 row2(5.0, 6.0, 7.0, 8.0);
    vec4 row3(9.0, 10.0, 11.0, 12.0);
    vec4 row4(13.0, 14.0, 15.0, 16.0);

    mat4 m(row1, row2, row3, row4);
    EXPECT_EQ(m[0], row1);
    EXPECT_EQ(m[1], row2);
    EXPECT_EQ(m[2], row3);
    EXPECT_EQ(m[3], row4);

    // Check if modification using index operator works
    m[0] = vec4(17.0, 18.0, 19.0, 20.0);
    EXPECT_EQ(m[0], vec4(17.0, 18.0, 19.0, 20.0));
}

TEST(Mat4Test, MultiplicationByScalar) {
    vec4 row1(1.0, 2.0, 3.0, 4.0);
    vec4 row2(5.0, 6.0, 7.0, 8.0);
    vec4 row3(9.0, 10.0, 11.0, 12.0);
    vec4 row4(13.0, 14.0, 15.0, 16.0);

    mat4 m(row1, row2, row3, row4);
    double scalar = 2.0;

    mat4 result = m * scalar;
    EXPECT_EQ(result[0], row1 * scalar);
    EXPECT_EQ(result[1], row2 * scalar);
    EXPECT_EQ(result[2], row3 * scalar);
    EXPECT_EQ(result[3], row4 * scalar);
}

TEST(Mat4Test, ScalarMultiplicationOrder) {
    vec4 row1(1.0, 2.0, 3.0, 4.0);
    vec4 row2(5.0, 6.0, 7.0, 8.0);
    vec4 row3(9.0, 10.0, 11.0, 12.0);
    vec4 row4(13.0, 14.0, 15.0, 16.0);

    mat4 m(row1, row2, row3, row4);
    double scalar = 2.0;

    mat4 result1 = m * scalar;
    mat4 result2 = scalar * m;

    // order should not matter
    EXPECT_EQ(result1[0], result2[0]);
    EXPECT_EQ(result1[1], result2[1]);
    EXPECT_EQ(result1[2], result2[2]);
    EXPECT_EQ(result1[3], result2[3]);
}