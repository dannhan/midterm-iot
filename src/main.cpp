#include "config.h"
#include "dht_sensor.h"
#include "lcd_status.h"
#include "led.h"
#include "rate.h"
#include "state.h"
#include "state_data.h"
#include "ultrasonic.h"
#include <Arduino.h>

#define TRIG 5
#define ECHO 18
#define MAX_DIST 80

#define RAIN_PIN 23
#define DHT_PIN 19

float prevLevel = 0;
unsigned long prevTime = 0;

Config cfg = {.maxDistance = 16,
              .smoothAlpha = 0.3,
              .alertRate = 2.0,
              .dangerLevel = 12.0,
              .humidityThreshold = 70};

void setup() {
  Serial.begin(115200);

  ultrasonicBegin(TRIG, ECHO);
  dhtBegin(DHT_PIN);
  rainBegin(RAIN_PIN);
  lcdBegin(21, 22);
  lcdSplash("Flood Monitor", "Init OK", 800);
  ledBegin(32, 33, 25);

  prevTime = millis();
}

SystemState sys = {0, 0};

void loop() {
  unsigned long now = millis();
  float dt = (now - sys.prevTime) / 1000.0;

  // --- INPUT ---
  float distance = readDistance(TRIG, ECHO);
  float humidity = readHumidity();
  float temperature = readTemperature();
  bool rain = isRaining();

  // --- TRANSFORM ---
  float level = computeLevel(distance, cfg.maxDistance);
  float smoothed = smooth(level, sys.prevLevel, cfg.smoothAlpha);
  float rate = computeRate(smoothed, sys.prevLevel, dt);

  SensorData data = {distance, level, smoothed, humidity, temperature};

  State state = computeState(data.smooth, rate, data.humidity, rain, cfg);

  // --- OUTPUT ---
  ledUpdate(state);
  lcdShowStatus(state, data.smooth, rate, data.humidity);

  Serial.printf("Distance=%.2f cm | Level=%.2f cm | Rate=%.2f cm/s | "
                "Humidity=%.2f %% | State=%s\n",
                distance, data.smooth, rate, data.humidity,
                stateToString(state));

  // --- UPDATE STATE ---
  sys.prevLevel = data.smooth;
  sys.prevTime = now;

  delay(600);
}
