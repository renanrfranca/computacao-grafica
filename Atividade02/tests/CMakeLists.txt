include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCES
  geometry/test_vec2.cpp
  geometry/test_vec3.cpp
  geometry/test_vec4.cpp
  geometry/test_mat2.cpp
  geometry/test_mat3.cpp
  geometry/test_mat4.cpp
)


add_executable(tests ${SOURCES})

target_link_libraries(
    tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)