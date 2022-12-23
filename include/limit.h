#ifndef LCC_ROBOTICS_22_23_INCLUDE_LIMIT_H_
#define LCC_ROBOTICS_22_23_INCLUDE_LIMIT_H_

#include <Arduino.h>

#include "utils.h"

// clang-format off
constexpr Range<int> PWM_LIMIT_POSITIVE{0, 127};
constexpr Range<int> PWM_LIMIT_NEGATIVE {-127, 0};
// clang-format on

// Simple function which prevents robot from committing self die by clamping the raws between min and max when limit switch is activated
inline int safety(bool activated, int raw, const Range<int>& range)
{
    if (!activated)
        return raw;
    return constrain(raw, range.first, range.second);
}

// https://www.embeddedrelated.com/showarticle/646.php
// Smooths out sudden motions
inline int limitSlew(int raw, int prev_out, int max_deviation)
{
    int delta = raw - prev_out;
    if (delta > max_deviation)
        delta = max_deviation;
    else if (delta < -max_deviation)
        delta = -max_deviation;
    return prev_out + delta;
}

#endif // LCC_ROBOTICS_22_23_INCLUDE_LIMIT_H_
