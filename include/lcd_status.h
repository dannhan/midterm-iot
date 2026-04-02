#pragma once

#include "state.h"

void lcdBegin(int sda, int scl);
void lcdSplash(const char *line1, const char *line2, unsigned long ms);

void lcdShowStatus(State state, float level, float rate, float humidity);
