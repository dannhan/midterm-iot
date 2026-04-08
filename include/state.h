#pragma once

#include "config.h"

enum class State { SAFE, ALERT, DANGER };

State computeState(float level, float rate, float humidity, bool isRaining,
                   const Config &cfg);

const char *stateToString(State s);
