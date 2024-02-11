/**
 * @file
 * @brief Contains the Object class that reads faces from a .obj and is hittable
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include "vec3.h"
#include "mat3.h"
#include "triangle.h"
#include "hittable_list.h"

using std::make_shared;
using std::shared_ptr;

/**
 * @class object
 * @brief Reads .obj files and stores geometric data such as vertices, normals, textures, and faces.
 *
 * This class extends hittable and provides functionality to parse .obj file format and extract geometric data.
 */
class object : public hittable {
    public:
        object(
            std::string _file_path, 
            int _scale = 1, 
            vec3 _shift = vec3(),
            vec3 _rotation = vec3()
        ) : file_path(_file_path), scale(_scale), shift(_shift), rotation(_rotation) {
            readObj();
        }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            if (triangle_list.hit(r, ray_t, rec))
                return true;

            return false;
        }

    private:
        std::string file_path;
        double scale;
        vec3 shift;
        vec3 rotation;

        std::vector<vec3> vertice_list;
        std::vector<vec3> normal_list;
        std::vector<vec3> texture_list;
        hittable_list triangle_list;

        point3 rotate_x(point3 point, double theta) {
            double sinTheta = sin(theta);
            double cosTheta = cos(theta);

            return point3(
                point.x(),
                point.y() * cosTheta - point.z() * sinTheta,
                point.z() * cosTheta + point.y() * sinTheta
            );
        }

        point3 rotate_y(point3 point, double theta) {
            double sinTheta = sin(theta);
            double cosTheta = cos(theta);

            return point3(
                point.x() * cosTheta + point.z() * sinTheta,
                point.y(),
                point.z() * cosTheta - point.x() * sinTheta
            );
        }

        point3 rotate_z(point3 point, double theta) {
            double sinTheta = sin(theta);
            double cosTheta = cos(theta);

            return point3(
                point.x() * cosTheta - point.y() * sinTheta,
                point.y() * cosTheta - point.x() * sinTheta,
                point.z()

            );
        }

        point3 rotate(point3 vertex, vec3 rotation_vector) {
            point3 result = vertex;
            rotation_vector[0] = degrees_to_radians(rotation_vector[0]);
            rotation_vector[1] = degrees_to_radians(rotation_vector[1]);
            rotation_vector[2] = degrees_to_radians(rotation_vector[2]);

            if (rotation_vector.x() != 0)
                result = rotate_x(result, rotation_vector.x());
            if (rotation_vector.y() != 0)
                result = rotate_y(result, rotation_vector.y());
            if (rotation_vector.z() != 0)
                result = rotate_z(result, rotation_vector.z());

            return result;    
        }
        
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

        mat3 getValuesFromIndexes(std::vector<int> indexes, std::vector<vec3> list) {
            mat3 data;
            data[0] = list[indexes[0]];
            data[1] = list[indexes[1]];
            data[2] = list[indexes[2]];
            return data;
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
                vertex *= scale;
                vertex += shift;
                vertex = rotate(vertex, rotation);
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
                // Possible formats: "f 1/1/1 2/2/2 3/3/3" and "f 1//1 2//2 3//3"
                std::istringstream iss(line.substr(2));
                std::vector<int> vertice_index_list;
                std::vector<int> texture_index_list;
                std::vector<int> normal_index_list;
                int a, b, c;

                for (int i = 0; i < 3; i++) {
                    char slash;
                    iss >> a >> slash;
                    if (iss.peek() == '/') {
                        b = 0;
                        iss >> slash >> c;
                    } else {
                        iss >> b >> slash >> c;
                    }
                                    
                    a--; b--; c--; // obj indices start at 1
                    
                    validate_index(a, vertice_list.size());
                    if (b >= 0)
                        validate_index(b, texture_list.size());
                    validate_index(c, normal_list.size());

                    vertice_index_list.push_back(a);
                    if (b >= 0)
                        texture_index_list.push_back(b);
                    normal_index_list.push_back(c);
                }

                shared_ptr<triangle> tri = make_shared<triangle>(
                    getValuesFromIndexes(vertice_index_list, vertice_list),
                    getValuesFromIndexes(normal_index_list, normal_list)
                );

                triangle_list.add(tri);            
            }
        }

        /**
         * @brief Reads an obj file and populates lists of vertices, textures, normals, and triangles.
         *
         * @throws Ends the program if the file cannot be opened
         */
        void readObj() {
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