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
     * Checks if the supplied index is valid for the given size
     *
     * @param index the index to validate
     * @param size the size to compare the index against
     */
    void validate_index(int index, int size) {
        if (index < 0 || index >= size) {
            std::cerr << "Error: OBJ index out of bounds" << std::endl;
            exit(1);
        }
    }

    /**
     * @brief Parses a line from a file containing vertex, texture, normal, or face data and
     * adds the parsed data to the respective lists.
     *
     * @param line the line to be parsed
     */
    void parseLine(const std::string &line) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream iss(line.substr(2));
            point3 vertex;
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
            int a, b, c;

            iss >> a >> b >> c;
            a--; b--; c--; // obj indices start at 1
            
            validate_index(a, vertice_list.size());
            validate_index(b, vertice_list.size());
            validate_index(c, vertice_list.size());
                
            triangle_list.push_back(mat3(vertice_list[a], vertice_list[b], vertice_list[c]));
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

    /**
     * @brief Shifts all vertices, normals, textures, and triangles by the specified shift vector.
     *
     * @param shift the vector by which to shift the objects
     */
    void shift_object(const vec3& shift) {
        for (int i = 0; i < vertice_list.size(); i++) {
            vertice_list[i] += shift;
        }
        for (int i = 0; i < normal_list.size(); i++) {
            normal_list[i] += shift;
        }
        for (int i = 0; i < texture_list.size(); i++) {
            texture_list[i] += shift;
        }
        for (int i = 0; i < triangle_list.size(); i++) {
            triangle_list[i][0] += shift;
            triangle_list[i][1] += shift;
            triangle_list[i][2] += shift;
        }        
    }
};

#endif