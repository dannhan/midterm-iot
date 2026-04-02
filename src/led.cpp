#include "led.h"
#include <Arduino.h>

static int green, yellow, red;

void ledBegin(int g, int y, int r) {
  green = g;
  yellow = y;
  red = r;

  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
}

void ledUpdate(State state) {
  digitalWrite(green, state == State::SAFE);
  digitalWrite(yellow, state == State::ALERT);
  digitalWrite(red, state == State::DANGER);
}
