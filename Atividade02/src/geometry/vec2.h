/**
 * @file
 * @brief Contains a class of a 2D vector and basic operations
 */

#ifndef VEC2_H
#define VEC2_H

#include <cmath>
#include <iostream>

using std::sqrt;

/**
 * @class vec2
 * @brief Represents a 2D vector
 *
 * The class also contains a few useful functions for vector operations
 */
class vec2 {
  public:
    double e[2];

    vec2() : e{0,0} {}
    vec2(double e0, double e1) : e{e0, e1} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec2 operator-() const { return vec2(-e[0], -e[1]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec2& operator+=(const vec2 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        return *this;
    }

    vec2& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        return *this;
    }

    vec2& operator/=(double t) {
        return *this *= 1/t;
    }

    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1];
    }
};

// point2 is just an alias for vec2, but useful for geometric clarity in the code.
using point2 = vec2;


// Vector Utility Functions

inline bool operator==(const vec2& u, const vec2& v) {
    return u.x() == v.x() && u.y() == v.y();
}

inline bool operator!=(const vec2& u, const vec2& v) {
    return !(u == v);
}

inline std::ostream& operator<<(std::ostream &out, const vec2 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec2 operator+(const vec2 &u, const vec2 &v) {
    return vec2(u.e[0] + v.e[0], u.e[1] + v.e[1]);
}

inline vec2 operator-(const vec2 &u, const vec2 &v) {
    return vec2(u.e[0] - v.e[0], u.e[1] - v.e[1]);
}

inline vec2 operator*(const vec2 &u, const vec2 &v) {
    return vec2(u.e[0] * v.e[0], u.e[1] * v.e[1]);
}

inline vec2 operator*(double t, const vec2 &v) {
    return vec2(t*v.e[0], t*v.e[1]);
}

inline vec2 operator*(const vec2 &v, double t) {
    return t * v;
}

inline vec2 operator/(vec2 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec2 &u, const vec2 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1];
}

inline double cross(const vec2 &u, const vec2 &v) {
    return u.e[0] * v.e[1] - u.e[1] * v.e[0];
}

inline vec2 unit_vector(vec2 v) {
    return v / v.length();
}

#endif