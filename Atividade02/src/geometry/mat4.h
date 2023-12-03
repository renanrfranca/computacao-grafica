#ifndef mat4_H
#define mat4_H

#include <cmath>
#include <iostream>

#include "vec4.h"

using std::sqrt;

class mat4 {
  public:
    vec4 r[3];

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

// Vector Utility Functions

// Matrix operations
inline mat4 operator*(const mat4 &mat, double scalar) {
    return mat4(mat[0] * scalar, mat[1] * scalar, mat[2] * scalar, mat[3] * scalar);
}

inline mat4 operator*(double scalar, const mat4& matrix) {
    return matrix * scalar;
}

#endif