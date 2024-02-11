/**
 * @file
 * @brief Contains an abstract class for 3D objects that can be hit by rays and 
 * the hit_record class that holds intersection details.
 */

#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"


/**
 * @class hit_record
 * @brief Represents the data recorded when a ray hits an object.
 *
 * This class holds the details of the intersection of a ray with a hittable object.
 * It includes the point of intersection, the normal at the intersection,
 * the parameter 't' from the ray equation, and a boolean indicating
 * whether the intersection was with the front face of the object.
 */
class hit_record {
  public:
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    /**
     * Sets the hit record normal vector.
     *
     * @param r the ray
     * @param outward_normal (assumed to have unit length).
     */
    void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
        // normal = outward_normal;
    }
};

/**
 * @class hittable
 * @brief Abstract class representing any object that can be hit by a ray.
 *
 * This class provides an interface for objects that can be intersected by rays.
 * The `hit` method updates a `hit_record` object with details of the intersection.
 */
class hittable {
  public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif