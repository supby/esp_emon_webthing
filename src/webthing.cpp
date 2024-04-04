#include "webthing.h"

void setupWebThing(String deviceName) {
  webThingAdapter = new WebThingAdapter(deviceName, WiFi.localIP(), 80, true);
  
  // TODO: add properties
}