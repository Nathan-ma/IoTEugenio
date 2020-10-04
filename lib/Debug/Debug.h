#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>
#include "Macros.h"

#ifndef PRINT_DEBUG
#define PRINT_DEBUG false
#endif

class DebugClass {

 private:
  bool const debug = PRINT_DEBUG;
  char const* TAG;

 public:
  /** @brief Class Constructor */
  DebugClass(const char* ClassTag) : TAG(ClassTag){};

  /** @brief Debug Print */
  void print(const char* fmt, ...);
  /** @brief Debug Override*/
  void print(const __FlashStringHelper* fmt, ...);

  /** @brief Error Print*/
  void error(const char* fmt, ...);
  /** @brief Error Override*/
  void error(const __FlashStringHelper* fmt, ...);

  /** @brief Warn Print*/
  void warn(const char* fmt, ...);
  /** @brief Warn Override*/
  void warn(const __FlashStringHelper* fmt, ...);
};

#endif