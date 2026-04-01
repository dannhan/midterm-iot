#include "ultrasonic.h"
#include <Arduino.h>

Ultrasonic ultrasonic(5, 18, 100); // max distance 100 cm

void setup() { Serial.begin(115200); }

void loop() {
  float distance = ultrasonic.readDistance();
  float level = ultrasonic.readLevel();
  float smoothLevel = ultrasonic.readSmoothedLevel();

  Serial.printf("Distance: %.2f | Level: %.2f | Smooth: %.2f\n", distance,
                level, smoothLevel);

  delay(600);
}
