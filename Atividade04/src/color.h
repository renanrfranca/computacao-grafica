#ifndef COLOR_H
#define COLOR_H

#include "geometry/vec3.h"

#include <iostream>

/**
 * @file
 * @brief An alias for vec3, holding color values
 */
using color = vec3;

/**
 * @brief Writes P3 PPM color values to the output stream
 * 
 * This function takes a color vector and writes the color values to the specified output stream
 * in the P3 PPM format.
 *
 * @param out The output stream where the P3 PPM color values will be written.
 * @param pixel_color The color vector to be written in P3 PPM format.
 */
void write_color(std::ostream &out, color pixel_color) {
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif