/**
 * @file projeto_final.cpp
 * @author Renan Rossignatti de França <renanrfranca@gmail.com>
 * @brief This file contains the main routine for this project
 */

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std::chrono;

#include "util/rtweekend.h"

#include "geometry/hittable.h"
#include "geometry/hittable_list.h"
#include "geometry/sphere.h"
#include "geometry/triangle.h"
#include "geometry/object.h"

#include "export_image.cpp"
#include "color.h"
#include "camera.h"
#include "circular_animation.h"

point3 circle_path(point3 &center, double radius, double step) {
    double t = degrees_to_radians(step);
    return center + radius * vec3(sin(t), 0, cos(t));
}

/**
 * @brief The main function that creates a gradient, a circle and a square image and saves them in P3 PPM and PNG format
 */
int main() {
    auto start = high_resolution_clock::now();

    hittable_list world;

    auto diffuse_maroon = make_shared<lambertian>(color(0.5, 0.0, 0.0));
    auto diffuse_blue = make_shared<lambertian>(color(0.2, 0.2, 0.3));
    auto glass   = make_shared<dielectric>(1.5);
    auto metal_gold  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.3);

    
    shared_ptr<object> star = make_shared<object>("../resources/20facestar.obj", metal_gold, .8, vec3(0, 2, 0), vec3(90, 0, 0));
    shared_ptr<sphere> sphere1 = make_shared<sphere>(point3(0,1,-2), 1.2, diffuse_maroon);
    shared_ptr<sphere> sphere2 = make_shared<sphere>(point3(0,3,-4), 1.2, glass);

    // Ground
    world.add(make_shared<sphere>(point3(0.0, -100, -1.0), 100.0, diffuse_blue));
    world.add(star);
    world.add(sphere1);
    world.add(sphere2);

    camera camera;

    camera.aspect_ratio      = 16.0 / 9.0;
    camera.image_width       = 1024;
    camera.samples_per_pixel = 200;
    camera.max_depth         = 100;
    camera.vfov     = 90;
    camera.lookat   = point3(0,1,0);
    camera.vup      = vec3(0,1,0);

    int seconds = 5;
    int frames_per_second = 15;
    int total_frames = seconds * frames_per_second;

    circular_animation camera_anim = circular_animation(
        point3(0, 4, 0),
        7.0,
        360.0/total_frames
    );

    circular_animation sphere1_anim = circular_animation(
        point3(0, 1, 0),
        3,
        720.0/total_frames
    );

    // int i = 8;
    for (int i = 0; i < total_frames; i++) {
        auto frame_start = high_resolution_clock::now();
        camera.lookfrom = camera_anim.get_position(i);
        star->rotate(vec3(0, 0, 360/total_frames));
        sphere1->set_center(sphere1_anim.get_position(i));
        camera.render(world, "frame_" + std::to_string(i));   

        auto frame_Stop = high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::seconds>(frame_Stop - frame_start);

        std::cout << "\rFrame " << i << " Rendering time: "
         << duration.count() << " seconds." << std::endl;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<minutes>(stop - start);
    std::cout << "Rendering time: "
         << duration.count() << " minutes." << std::endl;

    return 0; 
}
