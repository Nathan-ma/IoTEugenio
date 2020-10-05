#include <Arduino.h>
#include <Motor.h>
#include <Network.h>
#include <MQTT.h>
#include <QRCode.h>
#include <Eugenio.h>

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
  Serial.println("\033[0;31mTesting\033[0m");
  initServices();
  testMockSchema();
}

void loop() {
  qrReader.loop();
  MQTT.loop();
}