/**
 * @file
 * @brief Contains a class of a 2x2 matrix made from 2 rows of vec2 and basic operations
 */

#ifndef mat2_H
#define mat2_H

#include <cmath>
#include <iostream>

#include "vec2.h"

using std::sqrt;

/**
 * @class mat2
 * @brief Represents a 2x2 matrix
 *
 * The matrix is built using 2 rows of vec2 vectors
 * The class also contains a few useful functions for matrix operations
 */
class mat2 {
  public:
    vec2 r[2];

    mat2() {
        r[0] = vec2(1.0, 0);
        r[1] = vec2(0, 1.0);
    }

    mat2(const vec2& row1, const vec2& row2) {
        r[0] = row1;
        r[1] = row2;
    }

    vec2& operator[](int i) {
        return r[i];
    }

    const vec2& operator[](int i) const {
        return r[i];
    }

    double determinant() {
        return (cross(r[0], r[1]));
    }
};

inline mat2 operator*(const mat2 &mat, double scalar) {
    return mat2(mat[0] * scalar, mat[1] * scalar);
}

inline mat2 operator*(double scalar, const mat2& matrix) {
    return matrix * scalar;
}

#endif