#ifndef SECOND_CODE_H
#define SECOND_CODE_H

#include <Arduino.h>
#include <TimeAlarms.h>

extern TaskHandle_t second_core_handle;

/** @brief Second Core setup() equivalent */
void SecondCoreSetup();


#endif