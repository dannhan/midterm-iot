#pragma once
#include "state.h"

class LedController {
public:
    LedController(int greenPin, int yellowPin, int redPin);

    void begin();
    void update(State state);

private:
    int green;
    int yellow;
    int red;
};
