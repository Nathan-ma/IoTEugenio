#ifndef PUMP_H
#define PUMP_H

#include <Arduino.h>

#define PUMP_PIN 0

class PumpClass {
 private:
  int pin;
 public:
  /* Initializer Passing Classes pin */
  PumpClass(int pinNumber) : pin(pinNumber){};

  /** @brief Set Pump pins */
  void setup();

  /** @brief            Set Pump State
   *  @param[in] state  State of the Pump
   */
  void setState(bool state);

  /** @brief    Get Pimp State
   *  @returns  Pump State
   */
  bool getState() const {return digitalRead(pin)};
};

extern PumpClass Pump;

#endif