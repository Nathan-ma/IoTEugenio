#include "Eugenio.h"
#include <MQTT.h>
#include <NTP.h>

void sendToEugenio() {

  /* Creates Json object */
  DynamicJsonDocument jsonBuffer(JSON_OBJECT_SIZE(3) + 100);
  JsonObject root = jsonBuffer.to<JsonObject>();
  JsonObject payload = root.createNestedObject("payload");

  root["schema"] = "perfume_dispense";
  payload["perfume_one"] = EugenioData.perfume_one;
  payload["perfume_two"] = EugenioData.perfume_two;
  payload["perfume_three"] = EugenioData.perfume_three;
  payload["time_stamp"] = now();
  payload["customer_id"] = EugenioData.customer_id;
  
  MQTT.sendData(root);

}