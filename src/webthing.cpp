#include "webthing.h"
#include "settings.h"

WebThingAdapter* webThingAdapter;
const char *sensorTypes[] = {"EnergyMonitor", nullptr};
ThingDevice energyMonitorDevice(WEBTHING_DEVICE_ID, WEBTHING_DEVICE_TITLE, sensorTypes);
ThingProperty currentProperty("CurrentProperty", "CurrentProperty", NUMBER, "CurrentProperty");
ThingProperty voltageProperty("VoltageProperty", "VoltageProperty", NUMBER, "VoltageProperty");
ThingProperty instantaneousPowerProperty("InstantaneousPowerProperty", "InstantaneousPowerProperty", NUMBER, "InstantaneousPowerProperty");

void setupWebThing(String deviceName) {
  currentProperty.readOnly = true;
  currentProperty.title = "Current";

  voltageProperty.readOnly = true;
  voltageProperty.title = "Voltage";

  instantaneousPowerProperty.readOnly = true;
  instantaneousPowerProperty.title = "Voltage";

  energyMonitorDevice.id = deviceName;
  energyMonitorDevice.title = deviceName;
  energyMonitorDevice.addProperty(&currentProperty);
  energyMonitorDevice.addProperty(&voltageProperty);
  energyMonitorDevice.addProperty(&instantaneousPowerProperty);

  webThingAdapter = new WebThingAdapter(deviceName, WiFi.localIP(), 80, true);
  webThingAdapter->addDevice(&energyMonitorDevice);
  webThingAdapter->begin();
}

void updateThingProperties(double current, double voltage, double power) {
  ThingPropertyValue currentValue;
  currentValue.number = current;    
  currentProperty.setValue(currentValue);

  ThingPropertyValue voltageValue;
  voltageValue.number = voltage;    
  voltageProperty.setValue(voltageValue);

  ThingPropertyValue instantaneousPowerValue;
  instantaneousPowerValue.number = power;    
  instantaneousPowerProperty.setValue(instantaneousPowerValue);

  webThingAdapter->update();
}