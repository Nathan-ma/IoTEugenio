#include <Pump.h>

/** @brief Set Pump pins */
void PumpClass::setup() {
  pinMode(pin, OUTPUT);
}

/** @brief            Set Pump State
 *  @param[in] state  State of the Pump
 */
void PumpClass::setState(bool state) {
  digitalWrite(pin, state);
}

PumpClass Pump(PUMP_PIN);