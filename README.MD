
# A simple Conan 2.0 + CMake project - PNG inverter library&tool

This project build a library for inverting colors in png files and a simple commandline utility to do the same.

## Initial Conan setup

Requirements:
 - C++14 compatible compiler
 - Ninja
 - CMake 3.22.1
 - Conan 2.0.1

Following <https://docs.conan.io/2/installation.html>, <https://docs.conan.io/2/tutorial/consuming_packages/build_simple_cmake_project.html>

```
conan profile detect --force
```

## Developing png-inverter locally

To setup the workspace run:
```
conan install . --build=missing
```
This generates a build folder, and CMakeUserPresets.json for manual CMake usage.

To compile the package with changes and run unit tests via Conan run:
```
conan build .
```

To manually configure and build via CMake, and then run tests:
```
cmake --preset conan-default
cmake --build --preset conan-release
ctest --preset conan-release
```

To run the built binary and invert an image:
```
./build/Release/png-inverter-tool test_image.png inverted.png
```

## Building the package

```
conan create . -s build_type=Release -o png-inverter/0.0.1:shared=True --build=missing
```

