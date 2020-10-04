#include <Arduino.h>
#include <Motor.h>
#include <Network.h>
#include <MQTT.h>
#include <QRCode.h>

void initServices() {
  /* Connects to Wifi Netwokr */
  Network.connect();
  /* Initialize MQTT */
  MQTT.setup();
  /* Initialize Motor */
  Motor.setup();
  /* Initialize QR Reader */
  qrReader.setup();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  initServices();
  
}

void loop() {
  qrReader.loop();
}