#define LARGE_JSON_BUFFERS 1
#define ARDUINOJSON_USE_LONG_LONG 1
#define DEVICE_NAME "esp_emon_webthing"

#include <Arduino.h>
#include <ArduinoJson.h>

// logs
#include <ArduinoLog.h>

// webthings
#include <WebThingAdapter.h>
#include <Thing.h>

// OTA
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "wifi.h"

void setup() {
  Serial.begin(9600);
  while(!Serial && !Serial.available()){}

  Log.begin(LOG_LEVEL_VERBOSE, &Serial);

  String deviceName(DEVICE_NAME);
  deviceName.concat("-");
  deviceName.concat(ESP.getChipId());
  deviceName.toLowerCase();

  Log.info(F(CR "Setting up WiFi..." CR));
  
  setupWiFi(deviceName);

  Log.info(F(CR "Connected to WiFi." CR));
}

void loop() {
  
}

