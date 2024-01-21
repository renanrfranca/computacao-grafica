#include <gtest/gtest.h>
#include "obj_reader.h"
#include "geometry/vec3.h"
#include "geometry/mat3.h"

TEST(ObjReaderTest, ParseLine_Vertex) {
    ObjReader objReader;
    objReader.parseLine("v 1.0 2.0 3.0");
    ASSERT_EQ(objReader.vertice_list.size(), 1);
    EXPECT_EQ(objReader.vertice_list[0], vec3(1.0, 2.0, 3.0));
}

TEST(ObjReaderTest, ParseLine_Texture) {
    ObjReader objReader;
    objReader.parseLine("vt 0.5 0.5 0.5");
    ASSERT_EQ(objReader.texture_list.size(), 1);
    EXPECT_EQ(objReader.texture_list[0], vec3(0.5, 0.5, 0.5));
}

TEST(ObjReaderTest, ParseLine_Normal) {
    ObjReader objReader;
    objReader.parseLine("vn 0.1 0.2 0.3");
    ASSERT_EQ(objReader.normal_list.size(), 1);
    EXPECT_EQ(objReader.normal_list[0], vec3(0.1, 0.2, 0.3));
}

TEST(ObjReaderTest, ParseLine_Face) {
    ObjReader objReader;
    objReader.parseLine("f 1/1/1 2/2/2 3/3/3");
    ASSERT_EQ(objReader.triangle_list.size(), 1);
    EXPECT_EQ(objReader.triangle_list[0][0], vec3(1, 1, 1));
    EXPECT_EQ(objReader.triangle_list[0][1], vec3(2, 2, 2));
    EXPECT_EQ(objReader.triangle_list[0][2], vec3(3, 3, 3));
}