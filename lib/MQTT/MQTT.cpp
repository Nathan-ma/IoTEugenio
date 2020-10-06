#include "MQTT.h"

#include <Motor.h>

DebugClass DebugStatic("MQTT");

eugenio_info_t EugenioData;

/* =========== Static ============ */
void MQTTClass::messageReceived(char *topic, byte *payload, unsigned int length) {
  String message;
  {
    std::string temp((char *)payload, length);
    message = temp.c_str();
  }

  /* Handles Payload */
  message.remove(0, 0);
  message.remove(message.length());
  message.replace("\\", "");

  DebugStatic.warn("Recieving -> \nfrom Topic[%s]", topic);
  DebugStatic.warn("Payload -> %s", message.c_str());
  
  MQTT.handleMethods(message);
}

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
  Debug.print("Defining Service -> \nServer : %s \nPort %d", MQTT_HOST, MQTT_PORT);
  mqtt.setServer(MQTT_HOST, MQTT_PORT);
  mqtt.setCallback(MQTTClass::messageReceived);
}

/** @brief Connects to MQTT Broker 
 *  @return true if Success
 */
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

/** @brief  Subscribe to a MQTT topic 
 *  @return true if subscribed 
 */
bool MQTTClass::subscribe() {
  Debug.print("Subscribing");
  if (!mqtt.subscribe(MQTT_SUB)) {
    pubSubErr(mqtt.state());
    return false;
  }
  return true;
}

/** @brief                Handles Methods and payload recieved
 *  @param[in]  payload   Recieved payload
 */
void MQTTClass::handleMethods(String &payload) {
  if (payload.equals("")) {
    Debug.warn("Empty Payload Received, prob a Ping");
    return;
  }

  {
    StaticJsonDocument<512> doc;
    auto err = deserializeJson(doc, payload.c_str());
    if (err) {
      Debug.error(F("deserializeJson() failed: "));
      Debug.error(err.c_str());
    }
    Serial.println();
    serializeJsonPretty(doc, Serial);
    Serial.println();
    EugenioData.customer_id = doc["customer_id"].as<String>();
    EugenioData.selectPerfume = doc["select_perfume"].as<int>();
  }

  
  MotorClass::selectPerfume(EugenioData.selectPerfume);
}

/* ========== Public =========== */

/** @brief Try to stablishs the mqtt connection */
void MQTTClass::setup() {
  secureClient.setCACert(ca_cert);
  secureClient.setCertificate(client_cert);  // for client verification
  secureClient.setPrivateKey(privkey);
  /* Defines Information about the server */
  defineService();
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
  subscribe();
}

/** @brief            Send data to a topic
 *  @param[out] root  Json Object to be send
 */
void MQTTClass::sendData(JsonObject &root) {
  String target;
  {
    String mqtt_pub_topic = "devices/" + String(MQTT_USER) + "/messages/events/";
    target = mqtt_pub_topic;
  }

  char payload[measureJson(root) + 1];
  serializeJson(root, payload, sizeof(payload));
  Debug.warn("Sending -> %s", payload);
  Debug.warn("to Topic -> %s", target.c_str());
  if (!mqtt.publish(target.c_str(), payload, false)) {
    pubSubErr(mqtt.state());
  } else {
    Debug.print("Message Sent Successfully");
  }
}

MQTTClass MQTT;