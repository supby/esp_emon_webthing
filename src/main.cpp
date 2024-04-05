#include <Arduino.h>
#include <ArduinoJson.h>

// logs
#include <ArduinoLog.h>

#include "settings.h"
#include "webthing.h"
#include "ota.h"
#include "wifi.h"

#include "EmonLib.h"

EnergyMonitor emon;

void setup() {
  Serial.begin(9600);
  while(!Serial && !Serial.available()){}

  Log.begin(LOG_LEVEL_VERBOSE, &Serial);

  String deviceName(NETWORK_DEVICE_NAME_PREFIX);
  deviceName.concat("-");
  deviceName.concat(ESP.getChipId());
  deviceName.toLowerCase();

  Log.info(F(CR "Setting up WiFi..." CR));
  
  setupWiFi(deviceName);

  Log.info(F(CR "Connected to WiFi." CR));

  Log.info(F(CR "Setting up WebThing..." CR));

  setupWebThing(deviceName);

  Log.info(F(CR "Setting up WebThing complited." CR));

  Log.info(F(CR "Setting up OTA..." CR));

  setupOTA(deviceName.c_str());

  Log.info(F(CR "Setting up OTA completed." CR));

  Log.info(F(CR "Setting up EMON..." CR));

  emon.current(A0, 15);

  Log.info(F(CR "Setting up EMON completed." CR));

  Log.info(F(CR "Setup DONE." CR));
}

void loop() {
  // TODO: add webthing properties updating

  delay(1000);

  double Irms = emon.calcIrms(1480);

  double constantVolatge = 230;

  double power = constantVolatge * Irms;

  Log.info(F("Current: %D, Voltage: %D, Power: %D" CR), Irms, constantVolatge, power);
}

