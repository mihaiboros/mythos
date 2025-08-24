cmake_minimum_required(VERSION 3.29)
project(poc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(
    SOURCE_FILES
    app.cpp
    app.h
    main.cpp
    scene.cpp
    scene.h
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE hera)
target_link_libraries(${PROJECT_NAME} PRIVATE ares)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/glass.png"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/glass.png"
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/metal.png"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/metal.png"
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/stained.png"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/stained.png"
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/wing.png"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/wing.png"
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/wood.png"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/wood.png"
)