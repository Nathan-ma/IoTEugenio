#ifndef EUGENIO_H
#define EUGENIO_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <DataSet.h>

extern eugenio_info_t EugenioData;

void sendToEugenio();

#endif