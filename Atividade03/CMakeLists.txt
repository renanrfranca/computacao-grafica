cmake_minimum_required(VERSION 3.14)
project(Atividade03)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
add_subdirectory(tests)

set(SOURCES
    src/atividade3.cpp
    src/obj_reader.h
    src/geometry/vec3.h
    src/geometry/mat3.h
)

add_executable(${PROJECT_NAME} ${SOURCES})