cmake_minimum_required(VERSION 3.29)
project(poc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(
    SOURCE_FILES
    keymap.cpp
    keymap.h
    main.cpp
    scene.cpp
    scene.h
    systemgl.h
    window.cpp
    window.h
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL OpenGL::GLU)
