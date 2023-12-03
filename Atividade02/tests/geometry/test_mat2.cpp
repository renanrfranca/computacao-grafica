#include <gtest/gtest.h>
#include "geometry/mat2.h"

TEST(Mat2Test, DefaultConstructor) {
    mat2 m;
    EXPECT_EQ(m[0].x, 1.0);
    EXPECT_EQ(m[0].y, 0.0);
    EXPECT_EQ(m[1].x, 0.0);
    EXPECT_EQ(m[1].y, 1.0);
}

TEST(Mat2Test, CustomConstructor) {
    vec2 row1(1.0, 2.0);
    vec2 row2(3.0, 4.0);
    mat2 m(row1, row2);
    EXPECT_EQ(m[0].x, 1.0);
    EXPECT_EQ(m[0].y, 2.0);
    EXPECT_EQ(m[1].x, 3.0);
    EXPECT_EQ(m[1].y, 4.0);
}

TEST(Mat2Test, ScalarMultiplication) {
    vec2 row1(1.0, 2.0);
    vec2 row2(3.0, 4.0);
    mat2 m(row1, row2);
    mat2 result = m * 2.0;
    EXPECT_EQ(result[0].x, 2.0);
    EXPECT_EQ(result[0].y, 4.0);
    EXPECT_EQ(result[1].x, 6.0);
    EXPECT_EQ(result[1].y, 8.0);
}

TEST(Mat2Test, ScalarMultiplicationReverseOrder) {
    vec2 row1(1.0, 2.0);
    vec2 row2(3.0, 4.0);
    mat2 m(row1, row2);
    mat2 result = 2.0 * m;
    EXPECT_EQ(result[0].x, 2.0);
    EXPECT_EQ(result[0].y, 4.0);
    EXPECT_EQ(result[1].x, 6.0);
    EXPECT_EQ(result[1].y, 8.0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}