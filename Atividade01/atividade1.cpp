/**
 * @file
 * @author Renan Rossignatti de França <renanrfranca@gmail.com>
 * @brief This file contains the main routine for this exercise and functions for creating images with gradients, circles, and squares.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "export_image.cpp"

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
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width-1);
            auto g = 0;
            auto b = double(j) / (image_height-1);

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            output_stream << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    saveToPPM("gradient.ppm", output_stream.str());
    saveToPng("gradient.png", image_width, image_height, output_stream.str());
}

/**
 * @brief Creates an image of a circle.
 *
 * This function generates an image with a filled red circle on a white background.
 * The image is saved in both P3 PPM and PNG formats.
 */
void createCircle() {
    // Image
    int image_width = 255;
    int image_height = 255;
    int radius = 60;

    // Render
    std::ostringstream output_stream;

    output_stream << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            if (((i - image_width/2) * (i - image_width/2) + (j - image_height/2) * (j - image_height/2)) <= radius * radius) {
                output_stream << "255 0 0\n";
            } else {
                output_stream << "255 255 255\n"; 
            }                       
        }
    }

    saveToPPM("circle.ppm", output_stream.str());
    saveToPng("circle.png", image_width, image_height, output_stream.str());
}

/**
 * @brief Creates an image of a square.
 *
 * This function generates an image with a filled red square in the center on a white background.
 * The image is saved in both P3 PPM and PNG formats.
 */
void createSquare() {
    // Image
    int image_width = 256;
    int image_height = 256;
    int margin = 56;

    // Render
    std::ostringstream output_stream;

    output_stream << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            if (
                (i > (margin)) && 
                (i < (image_width - margin)) &&
                (j > (margin)) &&
                (j < (image_height - margin))
            ) {
                output_stream << "255 0 0\n";
            } else {
                output_stream << "255 255 255\n"; 
            }                       
        }
    }

    saveToPPM("square.ppm", output_stream.str());
    saveToPng("square.png", image_width, image_height, output_stream.str());
}

/**
 * @brief The main function that creates a gradient, a circle and a square image and saves them in P3 PPM and PNG format
 */
int main() {
    createGradient();
    createCircle();
    createSquare();
}
