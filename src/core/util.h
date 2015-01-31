#pragma once

#include <math.h>

template <typename T>
T wrap(T val, T min, T max) {
    if (val < min) return max;
    if (val > max) return min;
    return val;
}

template <typename T>
T clamp(T val, T min, T max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}
