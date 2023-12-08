#include <gtest/gtest.h>
#include "geometry/mat2.h"

TEST(Mat2Test, DefaultConstructor) {
    mat2 m;
    EXPECT_EQ(m[0][0], 1.0);
    EXPECT_EQ(m[0][1], 0.0);
    EXPECT_EQ(m[1][0], 0.0);
    EXPECT_EQ(m[1][1], 1.0);
}

TEST(Mat2Test, CustomConstructor) {
    vec2 row1(1.0, 2.0);
    vec2 row2(3.0, 4.0);
    mat2 m(row1, row2);
    EXPECT_EQ(m[0][0], 1.0);
    EXPECT_EQ(m[0][1], 2.0);
    EXPECT_EQ(m[1][0], 3.0);
    EXPECT_EQ(m[1][1], 4.0);
}

TEST(Mat2Test, IndexOperator) {
    vec2 row1(1.0, 2.0);
    vec2 row2(4.0, 5.0);

    mat2 m(row1, row2);
    EXPECT_EQ(m[0], row1);
    EXPECT_EQ(m[1], row2);

    m[0] = vec2(10.0, 11.0);
    EXPECT_EQ(m[0], vec2(10.0, 11.0));
}

TEST(Mat2Test, ScalarMultiplication) {
    vec2 row1(1.0, 2.0);
    vec2 row2(3.0, 4.0);
    mat2 m(row1, row2);
    mat2 result = m * 2.0;
    EXPECT_EQ(result[0][0], 2.0);
    EXPECT_EQ(result[0][1], 4.0);
    EXPECT_EQ(result[1][0], 6.0);
    EXPECT_EQ(result[1][1], 8.0);
}

TEST(Mat2Test, ScalarMultiplicationReverseOrder) {
    vec2 row1(1.0, 2.0);
    vec2 row2(3.0, 4.0);
    mat2 m(row1, row2);
    mat2 result = 2.0 * m;
    EXPECT_EQ(result[0][0], 2.0);
    EXPECT_EQ(result[0][1], 4.0);
    EXPECT_EQ(result[1][0], 6.0);
    EXPECT_EQ(result[1][1], 8.0);
}

TEST(Mat2Test, DeterminantCalculation) {
    mat2 identityMatrix;
    EXPECT_EQ(identityMatrix.determinant(), 1.0);

    mat2 nonTrivialMatrix(vec2(3.0, 1.0), vec2(4.0, 2.0));
    EXPECT_EQ(nonTrivialMatrix.determinant(), 2.0);
}