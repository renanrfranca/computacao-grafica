/**
 * @file triangle.h
 * @brief Contains the triangle, which represents a geometric triangle in 3D space.
 */
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../util/rtweekend.h"
#include "hittable.h"
#include "mat3.h"
#include "../util/interval.h"
#include "material.h"

/**
 * @class triangle
 * @brief Represents a geometric triangle in 3D space.
 *
 * This class encapsulates the properties of a triangle, including its vertices and normals at each 
 * vertex. It inherits from the hittable class, allowing it to be used to detect intersections with rays.
 *
 * @param points A mat3 containing the coordinates of the triangle's vertices.
 * @param normals A mat3 containing the normal vectors at each of the triangle's vertices.
 */
class triangle : public hittable {
    public:
        triangle(mat3 _points, mat3 _normals, shared_ptr<material> _material) : 
            points(_points), normals(_normals), mat(_material) {}

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            vec3 positionVector = points[0] - r.origin();

            double nDotDirection = dot(plane_normal, r.direction()); 

            if (fabs(nDotDirection) < kEpsilon) { // Ray is parallel to the plane and therefore a miss
                return false;
            }

            rec.t = -(dot(plane_normal, r.origin()) + D) / nDotDirection; //figure out t for intersection of ray with plane
            if (!ray_t.surrounds(rec.t)) return false; // Out of the interval
            if (rec.t < 0) return false; // Plane behind ray and therefore a miss

            // Inside-outside test
            rec.p = r.at(rec.t);
            
            vec3 C; // vector perpendicular to triangle's plane
            double u, v, w; // barycentric values
            
            vec3 AH = rec.p - points[0];
            C = cross(AB, AH);
            if (dot(plane_normal, C) < 0) return false; // P is on the right side

            vec3 BH = rec.p - points[1];
            C = cross(BC, BH);
            u = dot(plane_normal, C);
            if (u < 0) return false; // P is on the right side

            vec3 CH = rec.p - points[2];
            C = cross(CA, CH);
            v = dot(plane_normal, C);
            if (v < 0) return false; // P is on the right side

            u /= denom;
            v /= denom;
            w = 1 - u - v;

            // Calculate the normal at the intersection point using barycentric coordinates
            vec3 outward_normal = u * normals[0] + v * normals[1] + w * normals[2];
            outward_normal = unit_vector(outward_normal);

            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;
            return true;
        }

    private:
        mat3 points;
        mat3 normals;
        shared_ptr<material> mat;

        vec3 AB = points[1] - points[0]; 
        vec3 BC = points[2] - points[1]; 
        vec3 CA = points[0] - points[2]; 
        vec3 plane_normal = cross(AB, BC);
        double denom = dot(plane_normal, plane_normal);
        double D = dot(-plane_normal, points[0]);
};

#endif