# Mythos

Mythos is a hobby project aimed at creating a 3d graphics engine and testing rendering performance and optimizations.
The main goal is to have a reasonably complete engine which can efficiently render thousands of moving objects in a static environment.

For now it only works under Windows.

## Building

Install VSCode and the CMake / C++ plugins to build and run the app.
Or just run the cmake utility in the command line something like:

```sh
cmake -B build -S .
cmake --build build --config Release
```

## Keyboard interaction

- F1: switch between full screen and window mode
- L: enable/disable light
- K: start animations
- E/D: camera advance/retreat
- S/F: camera strafe left/right
- R/C: camera rise/descend
- Q/W: camera roll left/right
- mouse: camera pitch/yaw (only in full screen mode)

## Sub-projects

- poc: contains the application code
- hera: render engine library, currenlty implemented with OpenGL and Windows API
- ares: general support library
