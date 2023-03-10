#pragma once


#ifdef _WIN32
  #define PNG_INVERTER_EXPORT __declspec(dllexport)
#else
  #define PNG_INVERTER_EXPORT
#endif

PNG_INVERTER_EXPORT void png_inverter();
