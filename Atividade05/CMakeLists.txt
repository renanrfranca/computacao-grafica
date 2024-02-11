cmake_minimum_required(VERSION 3.14)
project(Atividade05)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/atividade5.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})