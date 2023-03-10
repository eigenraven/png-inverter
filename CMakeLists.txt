cmake_minimum_required(VERSION 3.22.1)
project(png-inverter CXX)

set(PNGINVERTER_BUILD_VERSION "UNSET" CACHE STRING "Version of png-inverter that's being built")

add_library(png-inverter src/png-inverter.cpp)
target_include_directories(png-inverter PUBLIC include)
target_compile_definitions(png-inverter PRIVATE "-DPNGINVERTER_BUILD_VERSION=\"${PNGINVERTER_BUILD_VERSION}\"")

set_target_properties(png-inverter PROPERTIES PUBLIC_HEADER "include/png-inverter.h")
install(TARGETS png-inverter)
