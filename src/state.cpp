#include "state.h"

State StateMachine::update(float level, float rate) {
    if (level > 60) {
        current = State::DANGER;
    } else if (rate > 2.0) {
        current = State::ALERT;
    } else {
        current = State::SAFE;
    }

    return current;
}

const char* stateToString(State s) {
    switch (s) {
        case State::SAFE: return "SAFE";
        case State::ALERT: return "ALERT";
        case State::DANGER: return "DANGER";
    }
    return "UNKNOWN";
}
