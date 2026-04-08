#include "rain.h"
#include <Arduino.h>

static int rainPin;

void rainBegin(int pin) {
  rainPin = pin;
  pinMode(rainPin, INPUT);
}

bool isRaining() { return digitalRead(rainPin) == LOW; }
