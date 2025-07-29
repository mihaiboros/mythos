cmake_minimum_required(VERSION 4.1)

# package manager to install dependencies from vcpkg.json
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
project(mythos)

add_subdirectory(ares)
add_subdirectory(hera)
add_subdirectory(poc)
