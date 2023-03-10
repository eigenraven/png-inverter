#include "png-inverter.h"
#include <algorithm>
#include <csetjmp>
#include <cstdio>
#include <fmt/color.h>
#include <iostream>
#include <libpng16/png.h>
#include <png.h>
#include <pngconf.h>
#include <stdexcept>
#include <string_view>

namespace png_inverter {
const char *get_version() {
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

void invert_png(const char *inFilePath, const char *outFilePath) {
  // Based off https://gist.github.com/niw/5963798
  // Error handling is simplified and incomplete
  FILE *pngFile = fopen(inFilePath, "r");

  png_structp png =
      png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if (!png)
    throw std::runtime_error("Could not create png struct");

  png_infop info = png_create_info_struct(png);
  if (!info)
    throw std::runtime_error("Could not create png info struct");

  // Set up png error handler
  if (setjmp(png_jmpbuf(png))) {
    throw std::runtime_error("Png error encountered");
  }

  png_init_io(png, pngFile);
  png_read_info(png, info);

  const uint32_t width = png_get_image_width(png, info);
  const uint32_t height = png_get_image_width(png, info);
  const uint32_t colorType = png_get_color_type(png, info);
  const uint32_t bitDepth = png_get_bit_depth(png, info);

  // Read into 8bpp, RGB
  if (bitDepth == 16) {
    png_set_strip_16(png);
  }
  if (colorType == PNG_COLOR_TYPE_PALETTE) {
    png_set_palette_to_rgb(png);
  }
  if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8) {
    png_set_expand_gray_1_2_4_to_8(png);
  }
  if (png_get_valid(png, info, PNG_INFO_tRNS)) {
    png_set_tRNS_to_alpha(png);
  }
  if (colorType == PNG_COLOR_TYPE_GRAY ||
      colorType == PNG_COLOR_TYPE_GRAY_ALPHA) {
    png_set_gray_to_rgb(png);
  }
  if (colorType == PNG_COLOR_TYPE_GRAY_ALPHA ||
      colorType == PNG_COLOR_TYPE_RGBA ||
      colorType == PNG_COLOR_TYPE_RGB_ALPHA) {
    png_set_strip_alpha(png);
  }
  png_read_update_info(png, info);

  std::vector<std::vector<png_byte>> rows(height);
  for (auto &row : rows) {
    row.resize(png_get_rowbytes(png, info));
  }
  std::vector<png_bytep> rowPointers(height, nullptr);
  for (size_t y = 0; y < rowPointers.size(); y++) {
    rowPointers[y] = rows[y].data();
  }
  png_read_image(png, rowPointers.data());
  fclose(pngFile);
  png_destroy_read_struct(&png, &info, nullptr);

  // Invert each row
  for (auto &row : rows) {
    invert_bytes(row.data(), row.size());
  }

  pngFile = fopen(outFilePath, "w");
  if (!pngFile) {
    throw std::runtime_error("Could not open png file for writing");
  }

  // Create a new png file
  png =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if (!png)
    throw std::runtime_error("Could not create png struct for writing");

  info = png_create_info_struct(png);
  if (!info)
    throw std::runtime_error("Could not create png info struct for writing");

  if (setjmp(png_jmpbuf(png))) {
    throw std::runtime_error("Png error encountered");
  }

  png_init_io(png, pngFile);

  png_set_IHDR(png, info, width, height, 8, PNG_COLOR_TYPE_RGB,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png, info);

  png_write_image(png, rowPointers.data());
  png_write_end(png, nullptr);

  fclose(pngFile);
  png_destroy_write_struct(&png, &info);
}

} // namespace png_inverter
