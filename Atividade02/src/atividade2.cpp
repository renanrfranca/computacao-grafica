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
#include "color.h"

/**
 * @brief Creates an image with a gradient.
 *
 * This function generates an image with a smooth color gradient from the top-left to the bottom-right corner.
 * The result is a gradient going from black to red horizontally and black to blue vertically, resulting in a purple bottom-right
 * The image is saved in both P3 PPM and PNG formats.
 */
void createGradient() {
    // Image
    int image_width = 256;
    int image_height = 256;

    // Render
    std::ostringstream output_stream;

    output_stream << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto pixel_color = color(double(i) / (image_width-1), 0, double(j) / (image_height-1));
            write_color(output_stream, pixel_color);
        }
    }

    saveToPPM("gradient.ppm", output_stream.str());
    saveToPng("gradient.png", image_width, image_height, output_stream.str());

    std::clog << "\rDone.                 \n";
}

/**
 * @brief The main function that creates a gradient, a circle and a square image and saves them in P3 PPM and PNG format
 */
int main() {
    createGradient();
}
