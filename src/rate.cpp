#include "rate.h"

float RateCalculator::compute(float current, float previous, float dt) {
    if (dt <= 0) return 0;
    return (current - previous) / dt;
}
