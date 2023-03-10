cmake_minimum_required(VERSION 3.22.1)
project(PackageTest CXX)

find_package(GTest REQUIRED CONFIG)

include(GoogleTest)

add_executable(test_png_inverter test.cpp)
target_link_libraries(test_png_inverter GTest::gtest GTest::gtest_main png-inverter)

gtest_discover_tests(test_png_inverter)
