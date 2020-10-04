#include "Network.h"
#include <WiFi.h>

/** @brief Connect to a wireless network */
void NetworkClass::connect() {
  /* Attempt to connect */
  Debug.print("Connecting ->");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PWD);

  /* If board dont connects in 8 seconds it will restart */
  if (!isConnected()) {
    ESP.restart();
  }
  Debug.print("We are connected to the network");
}

/** @brief    Check if the board is connected to a network
 *  @return   true if it is connected
 */
bool NetworkClass::isConnected() {
  /* Wait for WiFi Connection */
  while (WiFi.status() != WL_CONNECTED) {
    Debug.print(".");
    delay(500);
    attempts++;
    if (attempts > 15) {
      return false;
    }
  }
  attempts = 0;
  return true;
}

NetworkClass Network;