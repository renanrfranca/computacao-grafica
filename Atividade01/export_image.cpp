#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

std::string convertToP6(std::string data) {
    std::istringstream ppmStream(data);
    std::ostringstream outputP6;

    std::string _;
    ppmStream >> _ >> _ >> _ >> _;

    int red, green, blue;
    while (ppmStream >> red >> green >> blue) {        
        outputP6.put(static_cast<char>(red));
        outputP6.put(static_cast<char>(green));
        outputP6.put(static_cast<char>(blue));
    }

    return outputP6.str();
}

void saveToPng(std::string filename, int width, int height, std::string data) {
    std::string p6String = convertToP6(data);
    if (stbi_write_png(filename.c_str(), width, height, 3, p6String.c_str(), width * 3) == 0) {
        // Handle the error if the image couldn't be saved.
        printf("Error: Could not save the image to PNG format.\n");
    }
}

void saveToPPM(std::string filename, std::string data) {
    std::ofstream ppm_file(filename);
    ppm_file << data;
}