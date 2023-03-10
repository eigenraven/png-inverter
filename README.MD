
## Initial Conan setup

Requirements:
 - C++14 compatible compiler
 - CMake 3.22.1
 - Conan 2.0.1

Following <https://docs.conan.io/2/installation.html>, <https://docs.conan.io/2/tutorial/consuming_packages/build_simple_cmake_project.html>

```
conan profile detect --force
```

## Developing png-inverter locally

To setup the workspace run:
```
conan install .
```
This generates a build folder, and CMakeUserPresets.json for manual CMake usage.

To compile the package with changes and run unit tests via Conan run:
```
conan build .
```

To manually configure and build via CMake, and then run tests:
```
cmake --preset conan-release
cmake --build --preset conan-release
ctest --preset conan-release
```

## Building the package

```
conan create . -s build_type=Release -o png-inverter/0.0.1:shared=True --build=missing
```

