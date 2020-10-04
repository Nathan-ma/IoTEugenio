#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

#define SENSOR_PIN 0

class SensorClass {
 private:
  int pin;
  bool state;

 public:
  /* Initializer Passing Classes pin */
  SensorClass(int pinNumber) : pin(pinNUmber){};

  /** @brief Set Sensor pins */
  void setup();

  bool getState();
};

extern SensorClass Sensor;

#endif