#include "led.h"
#include <Arduino.h>

LedController::LedController(int g, int y, int r)
    : green(g), yellow(y), red(r) {}

void LedController::begin() {
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
}

void LedController::update(State state) {
  digitalWrite(green, state == State::SAFE ? HIGH : LOW);
  digitalWrite(yellow, state == State::ALERT ? HIGH : LOW);
  digitalWrite(red, state == State::DANGER ? HIGH : LOW);
}
