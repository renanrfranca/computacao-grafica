/**
 * @file
 * @brief This file contains functions for saving images to P3 PPM and PNG formats.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

/**
 * @brief Converts a P3 PPM image data to a P6 PPM image data.
 *
 * This function takes P3 PPM image data as input and converts it to P6 format.
 * The P3 format uses ASCII text, while P6 format uses binary data. This is then used 
 * when saving the image to png, since stb_image_write.h requires binary PPM.
 *
 * @param data The input P3 PPM image data.
 * @return The converted P6 PPM image data in binary format.
 */
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

/**
 * @brief Saves P3 PPM image data as a PNG file.
 *
 * This function converts the P3 PPM image data to binary format and saves it as a PNG file.
 * The width and height of the image are specified, along with the output file name.
 *
 * @param filename The name of the PNG file to be saved.
 * @param width The width of the image.
 * @param height The height of the image.
 * @param data The P3 PPM image data in ASCII format.
 */
void saveToPng(std::string filename, int width, int height, std::string data) {
    std::string p6String = convertToP6(data);
    if (stbi_write_png(filename.c_str(), width, height, 3, p6String.c_str(), width * 3) == 0) {
        // Handle the error if the image couldn't be saved.
        printf("Error: Could not save the image to PNG format.\n");
    }
}

/**
 * @brief Saves PPM image data to a file.
 *
 * This function takes P3 PPM image data and saves it to a file with the specified filename.
 *
 * @param filename The name of the P3 PPM file to be saved.
 * @param data The PPM image data to be saved.
 */
void saveToPPM(std::string filename, std::string data) {
    std::ofstream ppm_file(filename);
    ppm_file << data;
}