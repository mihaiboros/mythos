cmake_minimum_required(VERSION 3.29)
project(ares)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(
    SOURCE_FILES
    bbox3.h
    concepts.h
    cs3.h
    curve/curve.h
    curve/curve3d.h
    curve/line3d.h
    epsilon.h
    frustum.h
    matrix.h
    plane.h
    vec2.h
    vec3.h
)

add_library(${PROJECT_NAME} INTERFACE ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} INTERFACE "${CMAKE_SOURCE_DIR}")
