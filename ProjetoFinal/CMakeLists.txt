cmake_minimum_required(VERSION 3.14)
project(ProjetoFinal)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/projeto_final.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})