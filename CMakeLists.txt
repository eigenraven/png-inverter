cmake_minimum_required(VERSION 3.23)
project(png-inverter CXX)

set(PNGINVERTER_BUILD_VERSION "UNSET" CACHE STRING "Version of png-inverter that's being built")

# Export compile_commands.json for IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(fmt REQUIRED)
find_package(PNG REQUIRED)

add_library(png-inverter src/png-inverter.cpp)
target_include_directories(png-inverter PUBLIC include)
target_compile_features(png-inverter PUBLIC cxx_std_14)
target_link_libraries(png-inverter PUBLIC fmt::fmt PNG::PNG)
target_compile_definitions(png-inverter PRIVATE "-DPNGINVERTER_BUILD_VERSION=\"${PNGINVERTER_BUILD_VERSION}\"")

set_target_properties(png-inverter PROPERTIES PUBLIC_HEADER "include/png-inverter.h")

add_executable(png-inverter-tool src/bin/main.cpp)
target_link_libraries(png-inverter-tool PUBLIC fmt::fmt png-inverter)

if(NOT BUILD_TESTING STREQUAL OFF)
    enable_testing()
    add_subdirectory(tests)
endif()

install(TARGETS png-inverter)
