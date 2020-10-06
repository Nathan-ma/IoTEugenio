#include <Arduino.h>
#include <Motor.h>
#include <Network.h>
#include <MQTT.h>
#include <Eugenio.h>
#include <SecondCore.h>
#include <NTP.h>

void initServices() {
  /* Connects to Wifi Netwokr */
  Network.connect();
  /* Starts NTP */
  NTP.setup();
  /* Starts Second Core */
  SecondCoreSetup();
  /* Initialize MQTT */
  MQTT.setup();
  /* Initialize Motor */
  MotorClass::setupAll();
  
}

void setup() {
  Serial.begin(115200);
  Serial.println("\033[0;31mTesting\033[0m");
  initServices();
}

void loop() {
  MQTT.loop();
}