cmake_minimum_required(VERSION 3.14)
project(Atividade02)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(SOURCES
    src/atividade2.cpp
    src/stb_image_write.h
    src/export_image.cpp
    src/color.h
    src/geometry/vec2.h
    src/geometry/vec3.h
    src/geometry/vec4.h
    src/geometry/mat2.h
    src/geometry/mat3.h
    src/geometry/mat4.h
    tests/geometry/test_mat2.cpp
)

# Create an executable for your tests
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME}
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})