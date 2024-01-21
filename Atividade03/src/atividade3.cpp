/**
 * @file
 * @author Renan Rossignatti de França <renanrfranca@gmail.com>
 * @brief This file contains the main routine for this exercise, reading an obj file, storing the data and printing it to the console
 */

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "obj_reader.h"
#include "geometry/vec3.h"
#include "geometry/mat3.h"
#include <vector>

/**
 * @brief Prints the elements of the given vec3 list in a specific format.
 *
 * @param vec3_list list of vec3 elements to be printed
 */
void printVector(const std::string prefix, const std::vector<vec3> &vec3_list) {
    for (const auto& v : vec3_list) {
        std::cout << prefix << " (" << v[0] << ", " << v[1] << ", " << v[2] << ")" << std::endl;
    }
}

/**
 * @brief Prints the elements of the given face_list in a specific format.
 *
 * @param face_list a vector of mat3 representing the faces to be printed
 */
void printMat(const std::vector<mat3> &face_list) {
    for (const auto &face : face_list) {
        std::cout << "f (";
        for (int i = 0; i < 3; i++) {
            if (i > 0) std::cout << " ";
            std::cout << face[i][0] << "/" << face[i][1] << "/" << face[i][2];
        }
        std::cout << ")" << std::endl;
    }
}

/**
 * @brief The main function that calls ObjReader and prints the results
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: Inform the file path as an argument" << std::endl;
        exit(1);
    }

    ObjReader obj_reader;
    std::string file_path = argv[1];
    obj_reader.readObj(file_path);

    std::cout << "Vertice List:" << std::endl;
    printVector("v", obj_reader.vertice_list);

    std::cout << "Texture List:" << std::endl;
    printVector("vt", obj_reader.texture_list);

    std::cout << "Normal List:" << std::endl;
    printVector("vn", obj_reader.normal_list);

    std::cout << "Triangle List:" << std::endl;
    printMat(obj_reader.triangle_list);
}   