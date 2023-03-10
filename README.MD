
# A simple Conan 2.0 + CMake project - PNG inverter library&tool

This project build a library for inverting colors in png files and a simple commandline utility to do the same.

## Requirements

Supported operating systems include Windows Server 2022 and Ubuntu 22.04.

Install the following tools and make sure they are available on your PATH. (you can execute them from the commandline, check `ninja --version`, `cmake --version`, `conan --version`)

 - C++14 compatible compiler
 - [Ninja](https://ninja-build.org/)
 - [CMake 3.22.1](https://cmake.org/)
 - [Conan 2.0.1](https://conan.io/)

If you haven't used Conan 2 before, set up a default profile:
```
conan profile detect --force
```
Tweak it as necessary if you notice a setting you want to change in the commandline output.

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
./build/Release/Release/png-inverter-tool test_image.png inverted.png
```

Sources are in the `include/` and `src/` directories.

## Installing to local Conan cache

If you want to depend on this package via your local Conan cache, run the following:
```
conan create . -s build_type=Release --build=missing
```
You can then depend on `png-inverter/0.0.1`.

# Automated workflows

## Build & test

On every push to the `dev` branch or a non-draft pull request targetting `dev`:
 - The project is built in Debug&Release configurations on Windows&Ubuntu
 - Unit tests are run via CTest

## Release generation

When a tag named `v*` is pushed (for example `v1.0.1`), a GitHub release will be automatically generated containing the built static libraries and executables for every platform; and Doxygen documentation.
A tag can be removed and pushed again safely, this will delete the old release and create a new one.
