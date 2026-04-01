#include "lcd_status.h"
#include "ultrasonic.h"
#include <Arduino.h>

// Sama seperti main di origin/main: pin & jarak maks (cm)
Ultrasonic ultrasonic(5, 18, 8);
LcdStatus display;

void setup() {
  Serial.begin(115200);
  if (!display.begin()) {
    Serial.println(F("LCD init failed (cek I2C addr / kabel)."));
  }
}

void loop() {
  float level = ultrasonic.readLevel();
  float smoothLevel = ultrasonic.smooth(level);
  float distance = ultrasonic.readDistance();

  display.showReadings(distance, level, smoothLevel);

  Serial.printf("Level: %.2f | Smooth: %.2f\n", level, smoothLevel);

  delay(600);
}
