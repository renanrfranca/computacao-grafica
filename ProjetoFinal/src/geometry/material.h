/**
 * @file
 * @brief Contains classes that define materials with different properties
 */
#ifndef MATERIAL_H
#define MATERIAL_H

#include "../util/rtweekend.h"

class hit_record;

/**
 * @class material
 * @brief Abstract class representing a type of material and how it interacts with rays.
 */
class material {
  public:
    virtual ~material() = default;

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};

/**
 * @class lambertian
 * @brief Represents a Lambertian (diffuse) material.
 * 
 * @param albedo The color of the material
 * 
 * This material emits light in a random direction on each hit.
 */ 
class lambertian : public material {
  public:
    lambertian(const color& a) : albedo(a) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
    const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        
        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

  private:
    color albedo;
};

/**
 * @class metal
 * @brief Represents a metal material that reflects light.
 * 
 * @param albedo The color of the material
 * @param fuzz The fuzziness of the reflection. A value from 0 to 1
 * 
 * This material reflects most light that hits it.The fuzz parameter determines how much
 * fuzziness is added to the reflected ray.  
 */ 
class metal : public material {
  public:
    metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
    const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz*random_unit_vector());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

  private:
    color albedo;
    double fuzz;
};

/**
 * @class dielectric
 * @brief Represents a dielectric (glass-like) material
 * 
 * @param index_of_refraction The index of refraction of the material
 * 
 * This material emits light in a random direction on each hit. The
 * refraction_ratio is the ratio of the index of refraction of the
 * material being refracted.
 */
class dielectric : public material {
  public:
    dielectric(double index_of_refraction) : ir(index_of_refraction) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
    const override {
        attenuation = color(1.0, 1.0, 1.0);
        double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

        vec3 unit_direction = unit_vector(r_in.direction());
        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        vec3 direction;

        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, refraction_ratio);

        scattered = ray(rec.p, direction);
        return true;
    }

  private:
    double ir; // Index of Refraction

    static double reflectance(double cosine, double ref_idx) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1-ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }
};

#endif
