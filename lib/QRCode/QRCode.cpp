#include "QRCode.h"

/* ======= Public ========== */

/** @brief Setup the Camera */
void QRCodeClass::setup() {
  reader.setup();
  //reader.setDebug(true);
  Debug.print("Setup QRCode Reader");

  reader.begin();
  Debug.print("Begin QR Code reader");
}

/** @brief QRCode Loop Class */
void QRCodeClass::loop() {
  if (reader.receiveQrCode(&qrCodeData, 100)) {
    Debug.print("Found QRCode");
    if (qrCodeData.valid) {
      Debug.print("Payload: ");
      Debug.print((const char *)qrCodeData.payload);
      // TODO Do something with the payload
    } else {
      Debug.print("Invalid: ");
      Debug.print((const char *)qrCodeData.payload);
    }
  }
  delay(300);
}

QRCodeClass qrReader;