#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "export_image.cpp"

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

int main() {
    createGradient();
    createCircle();
    createSquare();
}
