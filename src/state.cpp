#include "state.h"
#include <Arduino.h>

State computeState(float level, float rate, float humidity) {
  if (isnan(humidity))
    humidity = 0;

  if (level > 60)
    return State::DANGER;
  if (rate > 2.0 && humidity > 70)
    return State::ALERT;
  if (rate > 3.5)
    return State::ALERT;

  return State::SAFE;
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
