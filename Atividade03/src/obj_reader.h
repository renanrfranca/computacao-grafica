/**
 * @file
 * @brief Contains the ObjReader class for reading .obj files and storing geometric data
 */

#ifndef OBJ_READER_H
#define OBJ_READER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "geometry/vec3.h"
#include "geometry/mat3.h"

/**
 * @class ObjReader
 * @brief Reads .obj files and stores geometric data such as vertices, normals, textures, and faces.
 *
 * This class provides functionality to parse .obj file format and extract
 * the geometric information into accessible lists.
 */
class ObjReader {
public:
    std::vector<vec3> vertice_list;
    std::vector<vec3> normal_list;
    std::vector<vec3> texture_list;
    std::vector<mat3> triangle_list; // list of faces composed by 3 vertices

    /**
     * @brief Parses a line from a file containing vertex, texture, normal, or face data and
     * adds the parsed data to the respective lists.
     *
     * @param line the line to be parsed
     */
    void parseLine(const std::string &line) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream iss(line.substr(2));
            vec3 vertex;
            iss >> vertex[0] >> vertex[1] >> vertex[2];
            vertice_list.push_back(vertex);
        } else if (line.substr(0, 3) == "vt ") {
            std::istringstream iss(line.substr(3));
            vec3 texture;
            iss >> texture[0] >> texture[1] >> texture[2];
            texture_list.push_back(texture);
        } else if (line.substr(0, 3) == "vn ") {
            std::istringstream iss(line.substr(3));
            vec3 normal;
            iss >> normal[0] >> normal[1] >> normal[2];
            normal_list.push_back(normal);
        } else if (line.substr(0, 2) == "f ") {
            std::istringstream iss(line.substr(2));
            mat3 face;
            vec3 &vertex = face[0];
            for (int i = 0; i < 3; i++) {
                vec3 vec;
                char slash;
                iss >> vec[0] >> slash >> vec[1] >> slash >> vec[2];
                face[i] = vec;
            }
            triangle_list.push_back(face);
        }
    }

    /**
     * @brief Reads an obj file and populates lists of vertices, textures, normals, and triangles.
     *
     * @param file_path the path to the obj file to be read
     *
     * @throws Ends the program if the file cannot be opened
     */
    void readObj(std::string file_path) {
        std::ifstream file(file_path);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                parseLine(line);
            }
            file.close();
        } else {
            std::cerr << "Error: Failure opening obj file: " << file_path << std::endl;
            exit(1);
        }
    }
};

#endif