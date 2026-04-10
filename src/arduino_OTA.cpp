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

    // Wait for connection to complete, give up after timeout
    unsigned long timestamp = millis();
    bool ledState = false;
    while ((WiFi.status() != WL_CONNECTED) && ((millis() - timestamp) < TIMEOUT))
    {
      digitalWrite(LED_BUILTIN, ledState);
      ledState = !ledState;
      delay(500);
    }

    // Check if connection was successful
    if (WiFi.status() == WL_CONNECTED)
    {
      // Initialize OTA
      ArduinoOTA.begin(WiFi.localIP(), BOT_WIFI_NAME, BOT_WIFI_UPLOAD_PASS, InternalStorage);
      Serial.println("OTA initialized successfully");
    }
    else
    {
      Serial.println("Failed to connect to WiFi, OTA not initialized");
    }
  }
}