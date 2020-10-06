#include <NTP.h>
#include <Alarm.h>

/** @brief Setup Ntp */
void NTPClass::setup() {
  timeClient.begin();
  timeClient.update();
  Debug.print("%s" ,timeClient.getFormattedTime());
  setupAlarm((time_t)timeClient.getEpochTime());

}

NTPClass NTP;