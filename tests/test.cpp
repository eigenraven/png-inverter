#include "../include/png-inverter.h"

#include "gtest/gtest.h"

namespace {
TEST(PngInverter, HasVersion) {
  EXPECT_NE(png_inverter::get_version(), "UNKNOWN");
  EXPECT_NE(png_inverter::get_version(), "UNDEFINED");
}

TEST(PngInverter, Inverts) {
  std::vector<uint8_t> bytes{0x00, 0xFF, 0x00, 0xFF};
  const std::vector<uint8_t> expected{0xFF, 0x00, 0xFF, 0x00};
  png_inverter::invert_bytes(bytes.data(), bytes.size());
  EXPECT_EQ(bytes, expected);
}
} // namespace
