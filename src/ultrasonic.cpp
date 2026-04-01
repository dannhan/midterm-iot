#include "ultrasonic.h"
#include <Arduino.h>

#define SOUND_SPEED 0.034

Ultrasonic::Ultrasonic(int trigPin, int echoPin, float maxDistance)
    : trig(trigPin), echo(echoPin), maxDist(maxDistance), prevLevel(0) {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

float Ultrasonic::readDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);
  float distance = duration * SOUND_SPEED / 2;

  return distance;
}

float Ultrasonic::readLevel(float distance) {
  float level = maxDist - distance;

  if (level < 0)
    level = 0;
  if (level > maxDist)
    level = maxDist;

  return level;
}

// smoothing sederhana (EMA)
float Ultrasonic::smooth(float level) {
  float smoothed = 0.7 * prevLevel + 0.3 * level;
  prevLevel = smoothed;
  return smoothed;
}
