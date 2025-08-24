cmake_minimum_required(VERSION 3.29)
project(hera)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(
    SOURCE_FILES
    blend.h
    camera.h
    color.h
    engine.cpp
    engine.h
    ext/stb_image.cpp
    ext/stb_image.h
    glass_parts.h
    image.cpp
    image.h
    keymap.h
    light.h
    opengl/heragl.h
    opengl/light_gl.h
    opengl/renderer.cpp
    renderer.h
    solid_parts.h
    texture.h
    vertex.h
    win/engine_os.cpp
    win/keymap.cpp
    win/window_impl.cpp
    win/window_impl.h
    win/window.cpp
    window.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}")

target_link_libraries(${PROJECT_NAME} PUBLIC ares)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL OpenGL::GLU)
find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC GLEW::GLEW)