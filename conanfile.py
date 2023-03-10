from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files.copy_pattern import copy
from os import path

class png_inverterRecipe(ConanFile):
    name = "png-inverter"
    version = "0.0.1"

    # Optional metadata
    license = "MIT"
    author = "Raven Szewczyk <git@eigenraven.me>"
    url = "https://github.com/eigenraven/png-inverter"
    description = "Simple PNG image inversion library and binary"
    topics = ("image", "graphics", "png")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "LICENSE", "src/*", "include/*", "tests/*"

    def validate(self):
        check_min_cppstd(self, "14")

    def requirements(self):
        self.requires("fmt/9.1.0")
        self.requires("libpng/1.6.39")

        self.test_requires("gtest/1.13.0")

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self, generator="Ninja Multi-Config")
        tc.cache_variables["PNGINVERTER_BUILD_VERSION"] = str(self.version)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if not self.conf.get("tools.build:skip_test", default=False):
            test_folder = path.join("tests", str(self.settings.build_type))
            self.run(path.join(test_folder, "test_png_inverter"))

    def package(self):
        cmake = CMake(self)
        cmake.install()
        copy(self, "LICENSE", src=self.source_folder, dst=path.join(self.package_folder, "licenses"))

    def package_info(self):
        self.cpp_info.libs = ["png-inverter"]

