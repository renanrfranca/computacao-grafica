cmake_minimum_required(VERSION 3.14)
project(Atividade04)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
add_subdirectory(tests)

set(SOURCES
    src/atividade4.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})