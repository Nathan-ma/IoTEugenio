#ifndef ALARM_H
#define ALARM_H

#include <Arduino.h>
#include <TimeAlarms.h>

/** @brief Set up the Alarms so we can perform on fetch every 5 minutes and print the time on every minute*/
void setupAlarm(time_t time);

#endif