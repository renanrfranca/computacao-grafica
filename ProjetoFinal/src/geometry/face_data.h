/**
* @file face_data.h
* @brief Contains the face_data class, a container for the face data extracted from .obj files
*/
#ifndef FACE_DATA_H
#define FACE_DATA_H

#include <vector>
#include <regex>

#include "vec3.h"
#include "triangle.h"
#include "material.h"
// #include "util/rtweekend.h"

/**
* @class face_data
* @brief A container for the face data extracted from .obj files
*
* @param vertice_index_list The list of vertice indexes
* @param normal_index_list The list of vertice normal indexes
*/
class face_data {
public:
    int A_index;
    int B_index;
    int C_index;
    int nA_index;
    int nB_index;
    int nC_index;

    
    /**
     * Matches face indexes to vertex and normal lists and generates a triangle object.
     *
     * @param vertice_list a vector of point3 objects representing all vertices of the object
     * @param normal_list a vector of vec3 objects representing all vertice normals of the object
     * @param mat a shared pointer to a material object to be used by the triangle
     *
     * @return a shared pointer to a triangle object
     */
    shared_ptr<triangle> make_triangle(std::vector<point3> vertice_list, std::vector<vec3> normal_list, shared_ptr<material> mat) {
        mat3 points = mat3(
            vertice_list[A_index],
            vertice_list[B_index],
            vertice_list[C_index]
        );

        mat3 normals = mat3(
            normal_list[nA_index],
            normal_list[nB_index],
            normal_list[nC_index]
        );

        return make_shared<triangle>(
            points,
            normals,
            mat
        );
    }

    /**
     * Decrements all indexes since obj indexes are not zero starting
     */
    void to_zero_starting_indices() {
        A_index--;
        B_index--;
        C_index--;
        nA_index--;
        nB_index--;
        nC_index--;
    }

    /**
     * Checks if all indexes are valid
     */ 
    void validate_indices(int vertice_list_size, int normal_list_size) {
        validate_index(A_index, vertice_list_size);
        validate_index(B_index, vertice_list_size);
        validate_index(C_index, vertice_list_size);
        validate_index(nA_index, normal_list_size);
        validate_index(nB_index, normal_list_size);
        validate_index(nC_index, normal_list_size);
    }

private:
    
    std::vector<int> vertice_index_list;
    std::vector<int> normal_index_list;

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
};

inline face_data read_format_a(std::string face_line) {
    char slash; // irrelevant
    char texture_index; // irrelevant
    face_data face;

    std::istringstream iss(face_line.substr(2));
    iss >> face.A_index >> slash >> texture_index >> slash >> face.nA_index;
    iss >> face.B_index >> slash >> texture_index >> slash >> face.nB_index;
    iss >> face.C_index >> slash >> texture_index >> slash >> face.nC_index;

    face.to_zero_starting_indices();
    return face;
}

inline face_data read_format_b(std::string face_line) {
    char slash; // irrelevant
    face_data face;

    std::istringstream iss(face_line.substr(2));
    iss >> face.A_index >> slash >> slash >> face.nA_index;
    iss >> face.B_index >> slash >> slash >> face.nB_index;
    iss >> face.C_index >> slash >> slash >> face.nC_index;


    face.to_zero_starting_indices();
    return face;
}

/**
 * @brief Parses a face line from an obj file and creates a face_data object
 * 
 * Formats accepted:
 * `f 1/1/1 2/2/2 3/3/3`
 * or
 * `f 1//1 2//2 3//3`
 * 
 * @param face_line the line to be parsed
 * 
 * @return a face_data object
 */
inline face_data from_obj_line(std::string face_line) {
    std::regex format_a_pattern(R"(f \d+\/\d+\/\d+ \d+\/\d+\/\d+ \d+\/\d+\/\d+\r?)");
    std::regex format_b_pattern(R"(f \d+\/\/\d+ \d+\/\/\d+ \d+\/\/\d+\r?)");

    if (std::regex_match(face_line, format_a_pattern)) 
        return read_format_a(face_line);
    
    if (std::regex_match(face_line, format_b_pattern))
        return read_format_b(face_line);
    
    // If neither format
    std::cerr << "Error: Invalid face data format: " << face_line << std::endl;
    exit(1);
}

#endif // FACE_DATA_H