#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <Debug.h>
#include "secrets.h"

#ifndef MQTT_HOST
#define MQTT_HOST "logicalis-eugeniostg-iothub.azure-devices.net"
#endif

#ifndef MQTT_USER
#define MQTT_USER "eb13529c-41a9-4bfe-8132-15f7cc58713f"
#endif

#ifndef MQTT_PORT
#define MQTT_PORT 8883
#endif

class MQTTClass {
 private:
  /* Instances */
  WiFiClientSecure secureClient;
  PubSubClient mqtt;
  DebugClass Debug;

  /* Methods */
  /** @brief Translate MQTT Erorr Code */
  void pubSubErr(int8_t MQTTErr);

  /** @brief Defines the server and the Callback function */
  void defineService();

  /** @brief Connects to MQTT Broker */
  bool connect();

 public:
  /* Constructor */
  MQTTClass() : mqtt(secureClient), Debug("MQTT") {}

  /* Methods */
  /** @brief Try to stablishs the mqtt connection */
  void setup();

  /** @brief            Send data to a topic
   *  @param[out] root  Json Object to be send
   */
  void sendData(JsonObject& root);

  /** @brief Updates MQTT */
  void loop() { mqtt.loop(); }
};

extern MQTTClass MQTT;

#endif