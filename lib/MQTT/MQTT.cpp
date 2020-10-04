#include "MQTT.h"

/* =========== Private =========== */

/** @brief Translate MQTT Erorr Code */
void MQTTClass::pubSubErr(int8_t MQTTErr) {
  if (MQTTErr == MQTT_CONNECTION_TIMEOUT)
    Debug.error("Connection tiemout");
  else if (MQTTErr == MQTT_CONNECTION_LOST)
    Debug.error("Connection lost");
  else if (MQTTErr == MQTT_CONNECT_FAILED)
    Debug.error("Connect failed");
  else if (MQTTErr == MQTT_DISCONNECTED)
    Debug.error("Disconnected");
  else if (MQTTErr == MQTT_CONNECTED)
    Debug.error("Connected");
  else if (MQTTErr == MQTT_CONNECT_BAD_PROTOCOL)
    Debug.error("Connect bad protocol");
  else if (MQTTErr == MQTT_CONNECT_BAD_CLIENT_ID)
    Debug.error("Connect bad Client-ID");
  else if (MQTTErr == MQTT_CONNECT_UNAVAILABLE)
    Debug.error("Connect unavailable");
  else if (MQTTErr == MQTT_CONNECT_BAD_CREDENTIALS)
    Debug.error("Connect bad credentials");
  else if (MQTTErr == MQTT_CONNECT_UNAUTHORIZED)
    Debug.error("Connect unauthorized");
}

/** @brief Defines the server and the Callback function */
void MQTTClass::defineService() {
  mqtt.setServer(MQTT_HOST, MQTT_PORT);
  //TODO Declare the Callback
  //mqtt.setCallback(MQTTClass::cbRecieved);
}

/** @brief Connects to MQTT Broker */
bool MQTTClass::connect() {
  /* Declares mqtt_user */
  String mqtt_user;
  /* Temp build the string and destroy it right after */
  {
    String temp = String(MQTT_HOST) + "/" + String(MQTT_USER) + "/api-version=2017-06-30";
    mqtt_user = temp;
  }

  if (mqtt.connect(MQTT_USER, mqtt_user.c_str(), NULL)) {
    Debug.print("Connected");
    return true;
  } else {
    Debug.warn("SSL Error Code -> ");
    char err_buf[100];
    secureClient.lastError(err_buf, 100);
    Debug.warn(err_buf);
    Debug.error("failed, reason -> ");
    pubSubErr(mqtt.state());
    return false;
  }
}

/** @brief            Send data to a topic
 *  @param[out] root  Json Object to be send
 */
void MQTTClass::sendData(JsonObject& root) {
  String target;
  {
    String mqtt_pub_topic = "devices/" + String(MQTT_USER) + "/messages/events/";
    target = mqtt_pub_topic;
  }
  char payload[measureJson(root) + 1];
  serializeJson(root, payload, sizeof(payload));
  if (!mqtt.publish(target.c_str(), payload, false)) {
    pubSubErr(mqtt.state());
  }
}

/* ========== Public =========== */

/** @brief Try to stablishs the mqtt connection */
void MQTTClass::setup() {
  /* Informa the board is trying to connect */
  Debug.print("Connecting");
  connect();
  while (!mqtt.connected()) {
    Debug.print("Trying aghain in 5 seconds");
    delay(5000);
    if (connect()) {
      Debug.print("I think it is connected");
      break;
    }
  }
}

// TODO Something to build the data package and use the private method so we can send the informations

MQTTClass MQTT;