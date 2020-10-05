#include "Eugenio.h"
#include <MQTT.h>

void testMockSchema() {
  DynamicJsonDocument jsonBuffer(JSON_OBJECT_SIZE(3) + 100);
  JsonObject root = jsonBuffer.to<JsonObject>();
  JsonObject payload = root.createNestedObject("payload");

  root["schema"] = "perfume_dispense";
  payload["qrcode"] = "www.qrcodeexample.com";
  payload["paper_amount"] = 50;
  //payload["deviceid"] = "1001";

  MQTT.sendData(root);

  
}