#include <Arduino.h>
#include <WiFiNINA.h>
#include <ArduinoOTA.h>

#include "arduino_OTA.h"
  
namespace arduino_OTA
{
  void init()
  {
    // Start connecting to wifi
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Wait for connection to complete
    bool ledState = false;
    while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(LED_BUILTIN, ledState);
      ledState = !ledState;
      delay(500);
    }
    // Initialize OTA
    ArduinoOTA.begin(WiFi.localIP(), BOT_WIFI_NAME, BOT_WIFI_UPLOAD_PASS, InternalStorage);
  }
}