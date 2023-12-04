#include <gtest/gtest.h>
#include "geometry/mat3.h"

TEST(Mat3Test, DefaultConstructor) {
    mat3 m;
    EXPECT_EQ(m[0], vec3(1.0, 0.0, 0.0));
    EXPECT_EQ(m[1], vec3(0.0, 1.0, 0.0));
    EXPECT_EQ(m[2], vec3(0.0, 0.0, 1.0));
}

TEST(Mat3Test, CustomConstructor) {
    vec3 row1(1.0, 2.0, 3.0);
    vec3 row2(4.0, 5.0, 6.0);
    vec3 row3(7.0, 8.0, 9.0);

    mat3 m(row1, row2, row3);
    EXPECT_EQ(m[0], row1);
    EXPECT_EQ(m[1], row2);
    EXPECT_EQ(m[2], row3);
}

TEST(Mat3Test, IndexOperator) {
    vec3 row1(1.0, 2.0, 3.0);
    vec3 row2(4.0, 5.0, 6.0);
    vec3 row3(7.0, 8.0, 9.0);

    mat3 m(row1, row2, row3);
    EXPECT_EQ(m[0], row1);
    EXPECT_EQ(m[1], row2);
    EXPECT_EQ(m[2], row3);

    m[0] = vec3(10.0, 11.0, 12.0);
    EXPECT_EQ(m[0], vec3(10.0, 11.0, 12.0));
}

TEST(Mat3Test, MultiplicationByScalar) {
    vec3 row1(1.0, 2.0, 3.0);
    vec3 row2(4.0, 5.0, 6.0);
    vec3 row3(7.0, 8.0, 9.0);

    mat3 m(row1, row2, row3);
    double scalar = 2.0;

    mat3 result = m * scalar;
    EXPECT_EQ(result[0], row1 * scalar);
    EXPECT_EQ(result[1], row2 * scalar);
    EXPECT_EQ(result[2], row3 * scalar);
}

TEST(Mat3Test, ScalarMultiplicationOrder) {
    vec3 row1(1.0, 2.0, 3.0);
    vec3 row2(4.0, 5.0, 6.0);
    vec3 row3(7.0, 8.0, 9.0);

    mat3 m(row1, row2, row3);
    double scalar = 2.0;

    mat3 result1 = m * scalar;
    mat3 result2 = scalar * m;

    // order should not matter
    EXPECT_EQ(result1[0], result2[0]);
    EXPECT_EQ(result1[1], result2[1]);
    EXPECT_EQ(result1[2], result2[2]);
}