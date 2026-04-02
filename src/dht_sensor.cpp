#include "dht_sensor.h"
#include <DHT.h>

#define DHTTYPE DHT11

static DHT dht(0, DHTTYPE); // dummy init

DHTSensor::DHTSensor(int p) : pin(p) {}

void DHTSensor::begin() {
  dht = DHT(pin, DHTTYPE);
  dht.begin();
}

float DHTSensor::readTemperature() { return dht.readTemperature(); }

float DHTSensor::readHumidity() { return dht.readHumidity(); }
