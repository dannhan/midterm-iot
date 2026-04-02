#include "state.h"
#include <Arduino.h>

State StateMachine::update(float level, float rate, float humidity) {

  // handle sensor error
  if (isnan(humidity)) {
    humidity = 0;
  }

  if (level > 60) {
    current = State::DANGER;
  } else if (rate > 2.0 && humidity > 70) {
    current = State::ALERT;
  } else if (rate > 3.5) { // fallback kalau humidity gagal
    current = State::ALERT;
  } else {
    current = State::SAFE;
  }

  return current;
}

const char *stateToString(State s) {
  switch (s) {
  case State::SAFE:
    return "SAFE";
  case State::ALERT:
    return "ALERT";
  case State::DANGER:
    return "DANGER";
  }
  return "UNKNOWN";
}
