#include "png-inverter.h"
#include <algorithm>
#include <fmt/color.h>
#include <iostream>
#include <string_view>

namespace png_inverter {
std::string_view get_version() {
#ifdef PNGINVERTER_BUILD_VERSION
  return PNGINVERTER_BUILD_VERSION;
#else
  return "UNKNOWN";
#endif
}

void print_version() {
  fmt::print(fg(fmt::color::light_green), "PNG Inverter version: {}\n",
             fmt::styled(get_version(), fmt::emphasis::bold));
}

void invert_bytes(uint8_t *bytes, size_t bytesSz) {
  for (size_t i = 0; i < bytesSz; i++) {
    bytes[i] = ~bytes[i];
  }
}
} // namespace png_inverter
