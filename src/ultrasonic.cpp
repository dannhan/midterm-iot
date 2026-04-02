#include "ultrasonic.h"
#include <Arduino.h>

#define SOUND_SPEED 0.034

void ultrasonicBegin(int trig, int echo) {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

float readDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH, 30000);
  if (duration == 0)
    return -1;

  return duration * SOUND_SPEED / 2;
}

float computeLevel(float distance, float maxDist) {
  float level = maxDist - distance;

  if (level < 0)
    level = 0;
  if (level > maxDist)
    level = maxDist;

  return level;
}

float smoothLevel(float current, float previous) {
  return 0.7 * previous + 0.3 * current;
}
