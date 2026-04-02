#pragma once

enum class State { SAFE, ALERT, DANGER };

class StateMachine {
public:
  State update(float level, float rate, float humidity);

private:
  State current = State::SAFE;
};

const char *stateToString(State s);
