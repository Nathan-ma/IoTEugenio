#include "SecondCore.h"

TaskHandle_t second_core_handle;

static void SecondCoreLoop(void * pvParameters);

/** @brief Second Core setup() equivalent */
void SecondCoreSetup() {
  xTaskCreatePinnedToCore(SecondCoreLoop, "SC", 4096, NULL, 1, &second_core_handle, 0);
}

/** @brief Second Core loop() equivalent */
static void SecondCoreLoop(void * pvParameters) {
  Serial.print("Second Core running on core - > ");
  Serial.println(xPortGetCoreID());

  for(;;) {
    Alarm.delay(0);
    vTaskDelay(10);
  }
}