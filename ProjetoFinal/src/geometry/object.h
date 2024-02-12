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
#include "mat4.h"
#include "triangle.h"
#include "hittable_list.h"
#include "material.h"
#include "face_data.h"

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
            shared_ptr<material> _material, 
            double _scale_factor = 1, 
            vec3 _shift = vec3(),
            vec3 _rotation = vec3()
        ) : file_path(_file_path), mat(_material), scale_factor(_scale_factor), shift(_shift), rotation(_rotation) {
            readObj();
            calculate_origin();
            rotate(rotation, false);
            translate(shift);
            scale(scale_factor);
            generate_triangles();
        }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            if (triangle_list.hit(r, ray_t, rec))
                return true;

            return false;
        }

        /**
         * Rotates the object using the given rotation vector.
         *
         * @param rotation_vector the vector specifying the rotation angles in degrees along the x, y, and z axes
         * @param redo_triangles determines if the triangles need to be regenerated after the rotation
         */
        void rotate(vec3 rotation_vector, bool redo_triangles = true) {
            point3 current_origin = object_origin;

            rotation_vector[0] = degrees_to_radians(rotation_vector[0]);
            rotation_vector[1] = degrees_to_radians(rotation_vector[1]);
            rotation_vector[2] = degrees_to_radians(rotation_vector[2]);
            
            translate(-current_origin);

            for (int i = 0; i < vertice_list.size(); i++) {                
                vertice_list[i] = rotate_x(vertice_list[i], rotation_vector.x());
                vertice_list[i] = rotate_y(vertice_list[i], rotation_vector.y());
                vertice_list[i] = rotate_z(vertice_list[i], rotation_vector.z());    
            }

            for (int i = 0; i < normal_list.size(); i++) {                
                normal_list[i] = rotate_x(normal_list[i], rotation_vector.x());
                normal_list[i] = rotate_y(normal_list[i], rotation_vector.y());
                normal_list[i] = rotate_z(normal_list[i], rotation_vector.z());    
            }

            translate(current_origin);

            // needed when rotating during rendering
            if (redo_triangles) 
                generate_triangles();
        }

        
        /**
         * Scales the object by the given factor.
         *
         * @param factor the scaling factor
         */
        void scale(double factor) {
            point3 current_origin = object_origin;
            vec4 aux;
            mat4 transform_mat;
            transform_mat = factor * transform_mat;
            transform_mat[3][3] = 1;
            
            translate(-current_origin);

            for (int i = 0; i < vertice_list.size(); i++) {
                aux = vec4(vertice_list[i].x(), vertice_list[i].y(), vertice_list[i].z(), 1);
                aux = transform_mat * aux;

                vertice_list[i] = point3(aux.x(), aux.y(), aux.z());
            }

            translate(current_origin);
        }

        /**
         * Translates the object using the given translation vector.
         *
         * @param t the vector specifying the translation distance along the x, y, and z axes
         */
        void translate(vec3 t) {
            mat4 transform_mat;
            vec4 aux;

            transform_mat[3][0] = t.x();
            transform_mat[3][1] = t.y();
            transform_mat[3][2] = t.z();

            for (int i = 0; i < vertice_list.size(); i++) {
                aux = vec4(vertice_list[i].x(), vertice_list[i].y(), vertice_list[i].z(), 1);
                aux = transform_mat * aux;

                vertice_list[i] = point3(aux.x(), aux.y(), aux.z());
            }

            object_origin += t;
        }

    private:
        std::string file_path;
        shared_ptr<material> mat;
        point3 object_origin;
        double scale_factor;
        vec3 shift;
        vec3 rotation;

        std::vector<vec3> vertice_list;
        std::vector<vec3> normal_list;
        std::vector<vec3> texture_list;
        std::vector<face_data> face_list;
        hittable_list triangle_list;

        vec3 rotate_x(vec3 target, double theta) {
            if (theta == 0) return target;
            
            mat4 transform_mat;
            transform_mat[1][1] = cos(theta);
            transform_mat[1][2] = -sin(theta);
            transform_mat[2][1] = sin(theta);
            transform_mat[2][2] = cos(theta);

            vec4 aux = vec4(target.x(), target.y(), target.z(), 1);
            aux = transform_mat * aux;

            return vec3(aux.x(), aux.y(), aux.z());
        }

        vec3 rotate_y(vec3 target, double theta) {
            if (theta == 0) return target;
            
            mat4 transform_mat;
            transform_mat[0][0] = cos(theta);
            transform_mat[0][2] = sin(theta);
            transform_mat[2][0] = -sin(theta);
            transform_mat[2][2] = cos(theta);

            vec4 aux = vec4(target.x(), target.y(), target.z(), 1);
            aux = transform_mat * aux;

            return vec3(aux.x(), aux.y(), aux.z());
        }

        vec3 rotate_z(vec3 target, double theta) {
            if (theta == 0) return target;
            
            mat4 transform_mat;
            transform_mat[0][0] = cos(theta);
            transform_mat[0][1] = -sin(theta);
            transform_mat[1][0] = sin(theta);
            transform_mat[1][1] = cos(theta);

            vec4 aux = vec4(target.x(), target.y(), target.z(), 1);
            aux = transform_mat * aux;

            return vec3(aux.x(), aux.y(), aux.z());
        }

        point3 calculate_origin() {
            point3 origin;
            
            for (auto point : vertice_list) {
                origin += point;
            }

            return origin / vertice_list.size(); // average of all vertices
        }

        /**
         * Generates triangles based on the face data read, and material of the object.
         */
        void generate_triangles() {
            triangle_list.clear();
            for (auto face_data : face_list) {
                triangle_list.add(face_data.make_triangle(vertice_list, normal_list, mat));
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
                face_data face = from_obj_line(line);
                face.validate_indices(vertice_list.size(), normal_list.size());
                face_list.push_back(from_obj_line(line));        
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