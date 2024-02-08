/**
 * @file
 * @author Renan Rossignatti de França <renanrfranca@gmail.com>
 * @brief This file contains the main routine for this exercise and creates a gradient using the new `color` class
 */

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "export_image.cpp"
#include "geometry/vec3.h"
#include "geometry/ray.h"
#include "color.h"
#include "obj_reader.h"

/**
 * @brief Check if a ray hits a triangle defined by its three vertices.
 * 
 * The function first determines the plane normal by doing cross product between AB and BC,
 * then if the plane is not parallel to the ray or behind it, uses an orientation test 
 * considering AB, BC and CAto determine if the ray hits the triangle
 *
 * @param A First vertex of the triangle
 * @param B Second vertex of the triangle
 * @param C Third vertex of the triangle
 * @param r Ray to check for intersection with the triangle
 *
 * @return True if the ray intersects with the triangle, false otherwise
 */
bool hit_triangle(const point3 A, const point3 B, const point3 C, const ray& r) {
    vec3 AB = B - A;
    vec3 BC = C - B;
    vec3 CA = A - C;

    vec3 planeNormal = cross(AB, BC);

    vec3 positionVector = A - r.origin();

    double D = dot(planeNormal, positionVector);

    if (dot(planeNormal, r.direction()) == 0) { // Ray is parallel to the plane and therefore a miss
        return false;
    }

    double t = (D - dot(planeNormal, r.origin())) / dot(planeNormal, r.direction()); //figure out t for intersection of ray with plane
    if (t < 0) { // Plane behind ray and therefore a miss
        return false;
    }

    // It hit the plane, does it hit the triangle?
    point3 hitPoint = r.at(t);

    vec3 AH = hitPoint - A;
    vec3 BH = hitPoint - B;
    vec3 CH = hitPoint - C;

    // Check if the hitpoint is inside the triangle (to the "left" of all edge vectors at once)
    if (
        dot(cross(AB, AH), planeNormal) >= 0 
        && dot(cross(BC, BH), planeNormal) >= 0 
        && dot(cross(CA, CH), planeNormal) >= 0
    ) return true;

    return false;
}

/**
 * @brief Checks if a ray hits a sphere.
 *
 * @param center the center of the sphere
 * @param radius the radius of the sphere
 * @param r the ray to be checked
 *
 * @return true if the ray hits the sphere, false otherwise
 */
bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}

/**
 * @brief Returns the color to draw the skybox of the scene, a gradient going from light blue to almost white.
 *
 * @param r the ray to calculate the gradient for
 *
 * @return the calculated color
 */
color gradient(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

/**
 * @brief Calculate the color of the ray for the sphere scene. 
 * 
 * All Rays that collide with the sphere will be colored red.
 *
 * @param r the ray to calculate the color for
 *
 * @return the color of the ray
 */
color ray_color_sphere(const ray& r) {
    if (hit_sphere(point3(0,0,-1), 0.5, r))
        return color(1, 0, 0);

    return gradient(r);
}

/**
 * @brief Calculate the color of the ray in a scene with one or more triangles.
 * 
 * @param triangle_list the list of triangles
 *
 * @param r the ray to calculate the color for
 *
 * @return the color of the ray
 */
color ray_color_triangles(const std::vector<mat3> triangle_list, const ray& r) {
    // The triangles will alternate in color between red, green and blue
    color cycle_colors[3] = {color(0, 1, 0), color(0, 0, 1), color(1, 0, 0)};

    for (int i = 0; i < triangle_list.size(); i++) {
        mat3 triangle = triangle_list[i];
        if (hit_triangle(triangle[0], triangle[1], triangle[2], r)) {
            // return a different color for each i          
            return cycle_colors[i % 3];
        }
    }
    
    return gradient(r);
}

/**
 * @brief Genenerates a PPM and a png image of a scene with a red sphere in a skybox
 *
 * @param image_width the width of the image
 * @param image_height the height of the image
 * @param pixel00_loc the location of the top-left pixel
 * @param pixel_delta_u the horizontal delta between pixels
 * @param pixel_delta_v the vertical delta between pixels
 * @param camera_center the center point of the camera
 */
void draw_sphere(const int image_width, const int image_height, const point3& pixel00_loc, const vec3& pixel_delta_u, const vec3& pixel_delta_v, const point3& camera_center) {
    std::ostringstream output_stream;

    output_stream << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color_sphere(r);
            write_color(output_stream, pixel_color);
        }
    }

    saveToPPM("sphere.ppm", output_stream.str());
    saveToPng("sphere.png", image_width, image_height, output_stream.str());
}

/**
 * @brief Genenerates a PPM and a png image of a scene with a green triangle in a skybox
 *
 * @param image_width the width of the image
 * @param image_height the height of the image
 * @param pixel00_loc the location of the top-left pixel
 * @param pixel_delta_u the horizontal delta between pixels
 * @param pixel_delta_v the vertical delta between pixels
 * @param camera_center the center point of the camera
 */
void draw_triangle(const int image_width, const int image_height, const point3& pixel00_loc, const vec3& pixel_delta_u, const vec3& pixel_delta_v, const point3& camera_center) {
    // Render
    std::ostringstream output_stream;

    output_stream << "P3\n" << image_width << " " << image_height << "\n255\n";

    mat3 triangle = mat3(vec3(0, 0.5, -1), vec3(-0.5, -0.5, -1), vec3(0.5, -0.5, -1));

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color_triangles(std::vector<mat3>{triangle}, r);
            write_color(output_stream, pixel_color);
        }
    }

    saveToPPM("triangle.ppm", output_stream.str());
    saveToPng("triangle.png", image_width, image_height, output_stream.str());
}

/**
 * @brief Genenerates a PPM and a png image of a scene with a teapot in a skybox
 *
 * @param image_width the width of the image
 * @param image_height the height of the image
 * @param pixel00_loc the location of the top-left pixel
 * @param pixel_delta_u the horizontal delta between pixels
 * @param pixel_delta_v the vertical delta between pixels
 * @param camera_center the center point of the camera
 */
void draw_object(const int image_width, const int image_height, const point3& pixel00_loc, const vec3& pixel_delta_u, const vec3& pixel_delta_v, const point3& camera_center) {
    ObjReader obj_reader;
    std::string file_path = "../resources/bule.obj";
    obj_reader.readObj(file_path);
    obj_reader.shift_object(vec3(0, -2, -4));
    std::ostringstream output_stream;

    output_stream << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color_triangles(obj_reader.triangle_list, r);
            write_color(output_stream, pixel_color);
        }
    }

    saveToPPM("object.ppm", output_stream.str());
    saveToPng("object.png", image_width, image_height, output_stream.str());
}

/**
 * @brief The main function that creates a gradient, a circle and a square image and saves them in P3 PPM and PNG format
 */
int main() {
     // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render
    draw_sphere(image_width, image_height, pixel00_loc, pixel_delta_u, pixel_delta_v, camera_center);
    draw_triangle(image_width, image_height, pixel00_loc, pixel_delta_u, pixel_delta_v, camera_center);
    draw_object(image_width, image_height, pixel00_loc, pixel_delta_u, pixel_delta_v, camera_center);

    std::clog << "\rDone.                 \n";
}
