#include <Sensor.h>

/** @brief    Get Sensor's State
 *  @returns  Sensor State
 */
bool SensorClass::getState() {
  state = digitalRead(pin);
  return state;
}

SensorClass Sensor(SENSOR_PIN);