#pragma once

#include <stdlib.h>
#include <stdint.h>

#include <string_view>

#ifdef _WIN32
  #define PNG_INVERTER_EXPORT __declspec(dllexport)
#else
  #define PNG_INVERTER_EXPORT
#endif

namespace png_inverter {
  PNG_INVERTER_EXPORT std::string_view get_version();
  PNG_INVERTER_EXPORT void print_version();
  PNG_INVERTER_EXPORT void invert_bytes(uint8_t* bytes, size_t bytesSz);
}
