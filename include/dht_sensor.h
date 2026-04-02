#pragma once

class DHTSensor {
public:
  DHTSensor(int pin);

  void begin();
  float readTemperature();
  float readHumidity();

private:
  int pin;
};
