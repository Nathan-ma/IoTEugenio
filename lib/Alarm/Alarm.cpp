#include <Alarm.h>

static void digitalClockDisplay();
static void printDigits(int digits);

/** @brief Set up the Alarms so we can perform on fetch every 5 minutes and print the time on every minute*/
void setupAlarm(time_t time) {
  setTime(time);
  Alarm.timerRepeat(60, digitalClockDisplay);
}

/** @brief Display the Time currently in the board */
static void digitalClockDisplay() {
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

/** @brief Prints the digits based on the time input
 *  @param[in]  digits  Print in clock digits format
 */
static void printDigits(int digits) {
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}