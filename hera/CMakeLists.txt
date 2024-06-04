cmake_minimum_required(VERSION 3.29)
project(hera)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(
    SOURCE_FILES
    color.h
    model.h
    sysgl.h
)

add_library(${PROJECT_NAME} INTERFACE ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} INTERFACE ares)
