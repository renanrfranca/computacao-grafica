/**
 * @file
 * @brief Contains a class of a ray, consisting of a point of origin and a direction vector
 */
#ifndef RAY_H
#define RAY_H

#include "vec3.h"

/**
 * @class ray
 * @brief Represents a ray
 *
 * The class represents a ray using a point of origin and a direction vector and provides a method to calculate the coordinates of a point on the ray given a t
 */
class ray {
  public:
    ray() {}

    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    point3 origin() const  { return orig; }
    vec3 direction() const { return dir; }

    point3 at(double t) const {
        return orig + t*dir;
    }

  private:
    point3 orig;
    vec3 dir;
};

#endif