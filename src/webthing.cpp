#include "webthing.h"
#include "settings.h"

WebThingAdapter* webThingAdapter;
const char *sensorTypes[] = {"EnergyMonitor", nullptr};
ThingDevice motionSensor(WEBTHING_DEVICE_ID, WEBTHING_DEVICE_TITLE, sensorTypes);
ThingProperty currentProperty("CurrentProperty", "CurrentProperty", NUMBER, "CurrentProperty");
ThingProperty voltageProperty("VoltageProperty", "VoltageProperty", NUMBER, "VoltageProperty");
ThingProperty instantaneousPowerProperty("InstantaneousPowerProperty", "InstantaneousPowerProperty", NUMBER, "InstantaneousPowerProperty");

void setupWebThing(String deviceName) {
  webThingAdapter = new WebThingAdapter(deviceName, WiFi.localIP(), 80, true);
  
  // TODO: add properties
}