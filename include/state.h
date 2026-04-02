#pragma once

#include "config.h"

enum class State { SAFE, ALERT, DANGER };

State computeState(float level, float rate, float humidity, const Config &cfg);

const char *stateToString(State s);
