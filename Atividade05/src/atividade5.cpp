/**
 * @file
 * @author Renan Rossignatti de França <renanrfranca@gmail.com>
 * @brief This file contains the main routine for this exercise and creates a gradient using the new `color` class
 */

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "rtweekend.h"

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

    world.add(make_shared<object>("../resources/tri-pyramid.obj", 1, vec3(0, 0, -2)));
    // world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    // world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    camera camera;

    camera.aspect_ratio      = 16.0 / 9.0;
    camera.image_width       = 400;
    camera.samples_per_pixel = 50;
    camera.max_depth         = 10;

    camera.vfov     = 90;
    camera.lookfrom = point3(0,0,-2);
    camera.lookat   = point3(0,0,0);
    camera.vup      = vec3(0,1,0);

    camera.render(world, "atividade5");
}
