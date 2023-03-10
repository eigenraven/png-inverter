#include "../include/png-inverter.h"

#include "gtest/gtest.h"

namespace {
TEST(PngInverter, HasVersion) {
  EXPECT_NE(png_inverter::get_version(), "UNKNOWN");
  EXPECT_NE(png_inverter::get_version(), "UNDEFINED");
}
} // namespace
