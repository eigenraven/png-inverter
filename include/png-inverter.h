#pragma once

#include <stdlib.h>
#include <stdint.h>

#include <string_view>
#include <vector>

#ifdef _WIN32
  #define PNG_INVERTER_EXPORT __declspec(dllexport)
#else
  #define PNG_INVERTER_EXPORT
#endif

/*! \brief All png inverter-related functions
   */
namespace png_inverter {
  /*! \brief Returns the version of the inverter library
   */
  PNG_INVERTER_EXPORT std::string_view get_version();
  /*! \brief Prints the version of the library to standard output
   */
  PNG_INVERTER_EXPORT void print_version();
  /*! \brief Takes a range of bytes, and inverts every bit in every byte in-place
      \param bytes The start pointer of the byte range to invert
      \param bytesSz The number of bytes to invert
   */
  PNG_INVERTER_EXPORT void invert_bytes(uint8_t* bytes, size_t bytesSz);
  /*! \brief Reads a PNG file, inverts all the colors and writes out a new PNG file.

      Currently converts everything to RGB8 with no alpha in the process.

      \param inFilePath Input file path
      \param outFilePath Output file path
   */
  PNG_INVERTER_EXPORT void invert_png(const char * inFilePath, const char* outFilePath);
}
