/**
 * @file circular_animation.h
 * @brief Contains the circular_animation class, which represents a circular path in 3D space
 */
#ifndef CIRCULAR_ANIMATION_H
#define CIRCULAR_ANIMATION_H

#include "geometry/vec3.h"
#include "util/rtweekend.h"

/**
 * @class circular_animation
 * @brief Represents a circular path around the Y axis in 3D space.
 * 
 * This class defines a circular path and allows it to be used to animate objects in 3D space.
 *
 * @param center The center point of the sphere.
 * @param radius The radius of the sphere.
 * @param step The angle step of the circular path.
 */
class circular_animation {
  public:
    circular_animation(point3 _center, double _radius, double _step) : center(_center), radius(_radius), step(_step) {
        step = degrees_to_radians(step);
    }

    /**
     * 
     * 
     * 
     * r(t) = c + ρ cos t(i) + ρ sin t(j), 0 ≤ t ≤ 2π
    */
    point3 get_position(int frame) {
        double t = frame * step;
        return center + radius * vec3(sin(t), 0, cos(t));
    }

  private:
    point3 center;
    double radius;
    double step;
};

#endif