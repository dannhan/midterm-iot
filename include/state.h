#pragma once

enum class State { SAFE, ALERT, DANGER };

State computeState(float level, float rate, float humidity);
const char *stateToString(State s);
