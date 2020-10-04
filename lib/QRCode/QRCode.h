#ifndef QR_CODE_H
#define QR_CODE_H

#include <Arduino.h>
#include <ESP32QRCodeReader.h>
#include <Debug.h>

#ifndef CAMERA_MODEL
#define CAMERA_MODEL CAMERA_MODEL_AI_THINKER
#endif

class QRCodeClass {
 private:
  /* Instances */
  DebugClass Debug;
  ESP32QRCodeReader reader;
  struct QRCodeData qrCodeData;

 public:
  /* Constructor */
  QRCodeClass() : Debug("Camera"), reader(CAMERA_MODEL) {}

  /** @brief Setup the Camera */
  void setup();

  /** @brief QRCode Loop Class */
  void loop();
};

extern QRCodeClass qrReader;

#endif