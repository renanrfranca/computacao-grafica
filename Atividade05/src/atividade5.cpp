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

    world.add(make_shared<object>("../resources/tri-pyramid.obj", 100, vec3(-6, 2, -14), vec3(0, 30, 0)));
    world.add(make_shared<object>("../resources/20facestar.obj", 1, vec3(0, -2, -2), vec3(90, 0, 0)));
    world.add(make_shared<object>("../resources/cube.obj", 2, vec3(4, 1.5, 0), vec3(30, 45, 0)));
    // world.add(make_shared<object>("../resources/dodecahedron.obj", 1, vec3(0, 5, 6)));
    // world.add(make_shared<sphere>(point3(4,5,-1), 4));

    world.add(make_shared<sphere>(point3(0,-100,-1), 100)); // Ground

    camera camera, camera2;

    camera.aspect_ratio      = 16.0 / 9.0;
    camera.image_width       = 400;
    camera.samples_per_pixel = 200;
    camera.max_depth         = 50;

    camera.vfov     = 60;
    camera.lookfrom = point3(0,3,-15);
    camera.lookat   = point3(0,2,0);
    camera.vup      = vec3(0,1,0);

    camera.render(world, "camera1");

    camera2.aspect_ratio      = 16.0 / 9.0;
    camera2.image_width       = 400;
    camera2.samples_per_pixel = 200;
    camera2.max_depth         = 50;

    camera2.vfov     = 60;
    camera2.lookfrom = point3(8,10,7);
    camera2.lookat   = point3(0,0,0);
    camera2.vup      = vec3(0,1,0);

    camera2.render(world, "camera2");
}
