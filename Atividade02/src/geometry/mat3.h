/**
 * @file
 * @brief Contains a class of a 3x3 matrix made from 3 rows of vec3 and basic operations
 */#ifndef mat3_H
#define mat3_H

#include <cmath>
#include <iostream>

#include "vec3.h"

using std::sqrt;

/**
 * @class mat3
 * @brief Represents a 3x3 matrix
 *
 * The matrix is built using 3 rows of vec3 vectors
 * The class also contains a few useful functions for matrix operations
 */
class mat3 {
  public:
    vec3 r[3];

    mat3() {
        r[0] = vec3(1.0, 0, 0);
        r[1] = vec3(0, 1.0, 0);
        r[2] = vec3(0, 0, 1.0);
    }

    mat3(const vec3& row1, const vec3& row2, const vec3& row3) {
        r[0] = row1;
        r[1] = row2;
        r[2] = row3;
    }

    vec3& operator[](int i) {
        return r[i];
    }

    const vec3& operator[](int i) const {
        return r[i];
    }

    double determinant() const {
        // 
        double a = r[0].x(), b = r[0].y(), c = r[0].z();
        double d = r[1].x(), e = r[1].y(), f = r[1].z();
        double g = r[2].x(), h = r[2].y(), i = r[2].z();

        return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
    }
};

inline mat3 operator*(const mat3 &mat, double scalar) {
    return mat3(mat[0] * scalar, mat[1] * scalar, mat[2] * scalar);
}

inline mat3 operator*(double scalar, const mat3& matrix) {
    return matrix * scalar;
}

#endif