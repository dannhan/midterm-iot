#pragma once

enum class State {
    SAFE,
    ALERT,
    DANGER
};

class StateMachine {
public:
    State update(float level, float rate);

private:
    State current = State::SAFE;
};

// helper (biar gampang print)
const char* stateToString(State s);
