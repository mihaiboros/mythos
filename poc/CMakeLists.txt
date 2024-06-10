cmake_minimum_required(VERSION 3.29)
project(poc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(
    SOURCE_FILES
    app.cpp
    app.h
    keymap.cpp
    keymap.h
    main.cpp
    scene.cpp
    scene.h
    window.cpp
    window.h
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL OpenGL::GLU)
target_link_libraries(${PROJECT_NAME} PRIVATE hera)
target_link_libraries(${PROJECT_NAME} PRIVATE ares)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/4_store.bmp"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/4_store.bmp")
