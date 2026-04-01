#include "lcd_status.h"
#include "ultrasonic.h"
#include <Arduino.h>

// Sama seperti main di origin/main: pin & jarak maks (cm)
Ultrasonic ultrasonic(5, 18, 80);
LcdStatus display;

void setup() {
  Serial.begin(115200);
  if (!display.begin()) {
    Serial.println(F("LCD init failed (cek I2C addr / kabel)."));
  }
}

void loop() {
  float distance = ultrasonic.readDistance();
  float level = ultrasonic.readLevel(distance);
  float smoothLevel = ultrasonic.smooth(level);

  display.showReadings(distance, level, smoothLevel);

  Serial.printf("Distance: %.2f | Level: %.2f | Smooth: %.2f\n", distance, level, smoothLevel);

  delay(600);
}
