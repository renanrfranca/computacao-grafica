#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../rtweekend.h"
#include "hittable.h"
#include "mat3.h"
#include "../util/interval.h"

class triangle : public hittable {
  public:
    mat3 points;
    mat3 normals;


    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        vec3 AB = points[1] - points[0];
        vec3 BC = points[2] - points[1];
        vec3 CA = points[0] - points[2];

        vec3 planeNormal = cross(AB, BC);

        vec3 positionVector = points[0] - r.origin();

        double D = dot(planeNormal, points[0]);

        if (fabs(dot(planeNormal, r.direction())) < 0) { // Ray is parallel to the plane and therefore a miss
            return false;
        }

        rec.t = (D - dot(planeNormal, r.origin())) / dot(planeNormal, r.direction()); //figure out t for intersection of ray with plane
        if (rec.t < 0) { // Plane behind ray and therefore a miss
            return false;
        }

        // It hit the plane, does it hit the triangle?
        rec.p = r.at(rec.t);

        vec3 AH = rec.p - points[0];
        vec3 BH = rec.p - points[1];
        vec3 CH = rec.p - points[2];

        // Check if the hitpoint is inside the triangle (to the "left" of all edge vectors at once)
        if (
            dot(cross(AB, AH), planeNormal) < 0 
            || dot(cross(BC, BH), planeNormal) < 0 
            || dot(cross(CA, CH), planeNormal) < 0
        ) return false;

        rec.set_face_normal(r, this->normals[0]);
        return true;
    }
};

#endif