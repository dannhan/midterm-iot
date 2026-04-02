#pragma once

void ultrasonicBegin(int trig, int echo);

float readDistance(int trig, int echo);
float computeLevel(float distance, float maxDist);
float smooth(float current, float previous, float alpha);
