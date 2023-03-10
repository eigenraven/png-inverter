cmake_minimum_required(VERSION 3.22.1)
project(png-inverter CXX)

add_library(png-inverter src/png-inverter.cpp)
target_include_directories(png-inverter PUBLIC include)

set_target_properties(png-inverter PROPERTIES PUBLIC_HEADER "include/png-inverter.h")
install(TARGETS png-inverter)
