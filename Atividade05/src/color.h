#ifndef COLOR_H
#define COLOR_H

#include "geometry/vec3.h"

#include <iostream>

/**
 * @file
 * @brief An alias for vec3, holding color values
 */
using color = vec3;

inline double linear_to_gamma(double linear_component)
{
    return sqrt(linear_component);
}

/**
 * @brief Writes P3 PPM color values to the output stream
 * 
 * This function takes a color vector and writes the color values to the specified output stream
 * in the P3 PPM format.
 *
 * @param out The output stream where the P3 PPM color values will be written.
 * @param pixel_color The color vector to be written in P3 PPM format.
 */
void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples.
    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // Apply the linear to gamma transform.
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // Write the translated [0,255] value of each color component.
    static const interval intensity(0.000, 0.999);
    out << static_cast<int>(256 * intensity.clamp(r)) << ' '
        << static_cast<int>(256 * intensity.clamp(g)) << ' '
        << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}

#endif