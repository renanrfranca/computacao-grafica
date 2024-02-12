/**
 * @file
 * @brief Contains a class of a 4x4 matrix made from 4 rows of vec4 and basic operations
 */

#ifndef mat4_H
#define mat4_H

#include <cmath>
#include <iostream>

#include "vec4.h"

using std::sqrt;

/**
 * @class mat4
 * @brief Represents a 4x4 matrix
 *
 * The matrix is built using 4 rows of vec4 vectors
 * The class also contains a few useful functions for matrix operations
 */
class mat4 {
  public:
    vec4 r[4];

    mat4() {
        r[0] = vec4(1.0, 0, 0, 0);
        r[1] = vec4(0, 1.0, 0, 0);
        r[2] = vec4(0, 0, 1.0, 0);
        r[3] = vec4(0, 0, 0, 1.0);
    }

    mat4(const vec4& row1, const vec4& row2, const vec4& row3, const vec4& row4) {
        r[0] = row1;
        r[1] = row2;
        r[2] = row3;
        r[3] = row4;
    }

    vec4& operator[](int i) {
        return r[i];
    }

    const vec4& operator[](int i) const {
        return r[i];
    }
};


inline mat4 operator*(const mat4 &mat, double scalar) {
    return mat4(mat[0] * scalar, mat[1] * scalar, mat[2] * scalar, mat[3] * scalar);
}

inline mat4 operator*(double scalar, const mat4& matrix) {
    return matrix * scalar;
}

inline vec4 operator*(const mat4& m, const vec4& v) {
    return vec4(
        m[0][0] * v.x() + m[1][0] * v.y() + m[2][0] * v.z() + m[3][0],
        m[0][1] * v.x() + m[1][1] * v.y() + m[2][1] * v.z() + m[3][1],
        m[0][2] * v.x() + m[1][2] * v.y() + m[2][2] * v.z() + m[3][2],
        m[0][3] * v.x() + m[1][3] * v.y() + m[2][3] * v.z() + m[3][3]
    );
}

#endif