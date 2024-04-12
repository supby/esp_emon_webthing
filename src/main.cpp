#include <Arduino.h>
#include <ArduinoJson.h>
#include <Ticker.h>
#include <math.h>

// logs
#include <ArduinoLog.h>

#include "settings.h"
#include "webthing.h"
#include "ota.h"
#include "wifi.h"

#include "EmonLib.h"

EnergyMonitor emon;
Ticker checkPropertiesTimer;

void checkProperties() {
  float Irms = roundf(emon.calcIrms(EMON_NUMBER_OF_SAMPLES) * 1000) / 1000;
  float constantVolatge = 230; // TODO: constant for now
  float power = constantVolatge * Irms;

  Log.info(F("Current: %D, Voltage: %D, Power: %D" CR), Irms, constantVolatge, power);

  updateThingProperties(Irms, constantVolatge, power);
}

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BOARD_LED_BUILTIN, OUTPUT);
  pinMode(A0, INPUT);

  digitalWrite(16, LOW);
  digitalWrite(LED_BUILTIN, LOW);

  delay(1000);

  Serial.begin(9600);
  while(!Serial && !Serial.available()){}

  Log.begin(LOG_LEVEL_VERBOSE, &Serial);

  Log.info(F("Starting Setup..." CR));

  String deviceName(NETWORK_DEVICE_NAME_PREFIX);
  deviceName.concat("-");
  deviceName.concat(ESP.getChipId());
  deviceName.toLowerCase();

  Log.info(F("Setting up WiFi..." CR));
  
  setupWiFi(deviceName);

  Log.info(F("Connected to WiFi." CR));

  Log.info(F("Setting up WebThing..." CR));

  setupWebThing(deviceName);

  Log.info(F("Setting up WebThing complited." CR));

  Log.info(F("Setting up OTA..." CR));

  setupOTA(deviceName.c_str());

  Log.info(F("Setting up OTA completed." CR));

  Log.info(F("Setting up EMON..." CR));

  emon.current(A0, EMON_ICAL);

  Log.info(F("Setting up EMON completed." CR));

  checkPropertiesTimer.attach(UPDATE_RATE_SEC, checkProperties);

  Log.info(F("Setup DONE." CR));
}

void loop() {
  ArduinoOTA.handle();
}



