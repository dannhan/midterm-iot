#include "dht_sensor.h"
#include <DHT.h>

#define DHTTYPE DHT11

static DHT dht(0, DHTTYPE);

void dhtBegin(int pin) {
  dht = DHT(pin, DHTTYPE);
  dht.begin();
}

float readTemperature() { return dht.readTemperature(); }

float readHumidity() { return dht.readHumidity(); }
