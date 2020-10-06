#ifndef NTP_H
#define NTP_H

#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Debug.h>

#ifndef TIME_ZONE
#define TIME_ZONE -3
#endif

class NTPClass {
 private:
  /* Instances */
  DebugClass Debug;
  WiFiUDP ntpUDP;
  NTPClient timeClient;

 public:
  /* Constructor */
  NTPClass() : Debug("NTP"), timeClient(ntpUDP, "us.pool.ntp.org", 3600 * TIME_ZONE, 60000){};

  /* Methods */
  /** @brief Setup Ntp */
  void setup();

};

extern NTPClass NTP;

#endif