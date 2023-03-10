#include "png-inverter.h"
#include <fmt/core.h>

int main(int argc, char **argv) {
  png_inverter::print_version();
  if (argc != 3) {
    fmt::print("Usage: {} input.png output.png",
               argc > 0 ? argv[0] : "(invalid argv[0]) png-inverter-tool");
    return 1;
  }
  png_inverter::invert_png(argv[1], argv[2]);
  return 0;
}
