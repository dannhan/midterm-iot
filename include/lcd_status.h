#pragma once

void lcdBegin(int sda, int scl);
void lcdSplash(const char *line1, const char *line2, unsigned long ms);

void lcdShowReadings(float distance, float level, float smooth);
