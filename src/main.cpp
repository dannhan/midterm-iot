#include "dht_sensor.h"
#include "lcd_status.h"
#include "led.h"
#include "rate.h"
#include "state.h"
#include "ultrasonic.h"
#include <Arduino.h>

#define TRIG 5
#define ECHO 18
#define MAX_DIST 80

#define DHT_PIN 19

float prevLevel = 0;
unsigned long prevTime = 0;

void setup() {
  Serial.begin(115200);

  ultrasonicBegin(TRIG, ECHO);
  dhtBegin(DHT_PIN);
  lcdBegin(21, 22);
  lcdSplash("Flood Monitor", "Init OK", 800);
  ledBegin(32, 33, 25);

  prevTime = millis();
}

void loop() {
  float distance = readDistance(TRIG, ECHO);
  float level = computeLevel(distance, MAX_DIST);
  float smooth = smoothLevel(level, prevLevel);

  float humidity = readHumidity();
  float temperature = readTemperature();

  unsigned long now = millis();
  float dt = (now - prevTime) / 1000.0;

  float rate = computeRate(smooth, prevLevel, dt);
  State state = computeState(smooth, rate, humidity);

  ledUpdate(state);

  lcdShowReadings(distance, level, smooth);

  Serial.printf("L: %.2f | R: %.2f | H: %.2f | T: %.2f | %s\n", smooth, rate,
                humidity, temperature, stateToString(state));

  prevLevel = smooth;
  prevTime = now;

  delay(600);
}
