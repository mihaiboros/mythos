cmake_minimum_required(VERSION 3.29)
project(hera)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(
    SOURCE_FILES
    color.h
    ext/stb_image.cpp
    ext/stb_image.h
    image.cpp
    image.h
    model.h
    sysgl.h
    vertex.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC ares)
