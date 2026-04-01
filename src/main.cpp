#include "ultrasonic.h"
#include <Arduino.h>

// max distance 8 cm
Ultrasonic ultrasonic(5, 18, 8);

void setup() { Serial.begin(115200); }

void loop() {
  float level = ultrasonic.readLevel();
  float smoothLevel = ultrasonic.smooth(level);

  Serial.printf("Level: %.2f | Smooth: %.2f\n", level, smoothLevel);

  delay(600);
}
