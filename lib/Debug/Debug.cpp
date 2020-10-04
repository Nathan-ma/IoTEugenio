#include "Debug.h"

/** @brief Debug Print */
void DebugClass::print(const char* fmt, ...) {
  char buf[128];
  va_list arg;
  va_start(arg, fmt);
  vsnprintf(buf, sizeof(buf), fmt, arg);
  va_end(arg);

  if (debug) {
    Serial.printf("[%s] : %s \r\n", TAG, buf);
  } else {
    ESP_LOGD(TAG, "%s", buf);
  }
}

/** @brief Debug Override*/
void DebugClass::print(const __FlashStringHelper* fmt, ...) {
  char buf[128];
  va_list arg;
  va_start(arg, fmt);
  vsnprintf(buf, sizeof(buf), (const char*)fmt, arg);
  va_end(arg);

  if (debug) {
    Serial.printf("[%s] : %s \r\n", TAG, buf);
  } else {
    ESP_LOGD(TAG, "%s", buf);
  }
}

/** @brief Error Print*/
void DebugClass::error(const char* fmt, ...) {
  char buf[128];
  va_list arg;
  va_start(arg, fmt);
  vsnprintf(buf, sizeof(buf), fmt, arg);
  va_end(arg);

  if (debug) {
    Serial.printf("[ERR][%s] : %s \r\n", TAG, buf);
  } else {
    ESP_LOGE(TAG, "%s", buf);
  }
}

/** @brief Error Override*/
void DebugClass::error(const __FlashStringHelper* fmt, ...) {
  char buf[128];
  va_list arg;
  va_start(arg, fmt);
  vsnprintf(buf, sizeof(buf), (const char*)fmt, arg);
  va_end(arg);

  if (debug) {
    Serial.printf("[ERR][%s] : %s \r\n", TAG, buf);
  } else {
    ESP_LOGE(TAG, "%s", buf);
  }
}

/** @brief Warn Print*/
void DebugClass::warn(const char* fmt, ...) {
  char buf[128];
  va_list arg;
  va_start(arg, fmt);
  vsnprintf(buf, sizeof(buf), fmt, arg);
  va_end(arg);

  if (debug) {
    Serial.printf("[WARN][%s] : %s \r\n", TAG, buf);
  } else {
    ESP_LOGW(TAG, "%s", buf);
  }
}

/** @brief Warn Override*/
void DebugClass::warn(const __FlashStringHelper* fmt, ...) {
  char buf[128];
  va_list arg;
  va_start(arg, fmt);
  vsnprintf(buf, sizeof(buf), (const char*)fmt, arg);
  va_end(arg);

  if (debug) {
    Serial.printf("[WARN][%s] : %s \r\n", TAG, buf);
  } else {
    ESP_LOGW(TAG, "%s", buf);
  }
}