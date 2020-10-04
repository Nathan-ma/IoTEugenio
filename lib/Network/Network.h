#ifndef NETWORK_H
#define NETOWKR_H

#include <Arduino.h>
#include <Debug.h>

/* Defining important constants but expecting them to be defined as flags in build time */
#ifndef WIFI_SSID
#define WIFI_SSID "Wifi here"
#endif

#ifndef WIFI_PWD
#define WIFI_PWD "Password here"
#endif

class NetworkClass {
 private:
  /* Instances */
  DebugClass Debug;
  /* Varaibles */
  int attempts;

  /* Methoods */
  /** @brief    Check if the board is connected to a network
   *  @return   true if it is connected
   */
  bool isConnected();

 public:
  /* Constructor */
  NetworkClass() : Debug("Network"){};
  /** @brief Connect to a wireless network */
  void connect();
};

extern NetworkClass Network;

#endif