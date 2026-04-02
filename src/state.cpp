#include "state.h"
#include "config.h"
#include <Arduino.h>

State computeState(float level, float rate, float humidity, const Config &cfg) {
  if (isnan(humidity))
    humidity = 0;

  if (level > cfg.dangerLevel)
    return State::DANGER;

  if (rate > cfg.alertRate && humidity > cfg.humidityThreshold)
    return State::ALERT;

  if (rate > cfg.alertRate * 1.5)
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
