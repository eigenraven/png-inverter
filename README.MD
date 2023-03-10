
## Initial Conan setup

Following <https://docs.conan.io/2/installation.html>, <https://docs.conan.io/2/tutorial/consuming_packages/build_simple_cmake_project.html>

```
conan profile detect --force
```

## Building the package

```
conan create . -s build_type=Release -o png-inverter/0.0.1:shared=True
```

