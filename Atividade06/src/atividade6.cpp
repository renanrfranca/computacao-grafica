/**
 * @file
 * @author Renan Rossignatti de França <renanrfranca@gmail.com>
 * @brief This file contains the main routine for this exercise and creates a gradient using the new `color` class
 */

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "util/rtweekend.h"

#include "geometry/hittable.h"
#include "geometry/hittable_list.h"
#include "geometry/sphere.h"
#include "geometry/triangle.h"
#include "geometry/object.h"

#include "export_image.cpp"
#include "color.h"
#include "camera.h"

/**
 * @brief The main function that creates a gradient, a circle and a square image and saves them in P3 PPM and PNG format
 */
int main() {
    hittable_list world;

    auto diffuse_green = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto diffuse_blue = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto glass   = make_shared<dielectric>(1.5);
    auto metal_gold  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.1);

    // Ground
    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, diffuse_green));
    // Diffuse blue sphere in the middle
    world.add(make_shared<sphere>(point3( 2.7,    1, -2.5),   1, diffuse_blue));
    
    // Gold 20 face star
    world.add(make_shared<object>("../resources/20facestar.obj", metal_gold, 1, vec3(0, -2, -2), vec3(90, 0, 0)));
    // Glass cube
    world.add(make_shared<object>("../resources/cube.obj", glass, 3, vec3(4, 1.5, 0), vec3(30, 45, 0)));

    camera camera;

    camera.aspect_ratio      = 16.0 / 9.0;
    camera.image_width       = 400;
    camera.samples_per_pixel = 300;
    camera.max_depth         = 100;

    camera.vfov     = 70;
    camera.lookfrom = point3(4,4,4);
    camera.lookat   = point3(3,2,0);
    camera.vup      = vec3(0,1,0);

    camera.render(world, "camera");
}
