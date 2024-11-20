#ifndef EXTRA_HPP
#define EXTRA_HPP
#include <stdint.h>
#include <limits>
#include <cmath>

#include "Vector3D.h"

static const double PI = 3.14159265358979323846;

/// <summary>
/// Less acurate but faster square root algorithm
/// </summary>
/// <param name="number">The number to take the root of</param>
/// <returns>square root</returns>
inline float fastSqrt(float number) {
    if (number == 0) return 0;
    int32_t i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *reinterpret_cast<int32_t*>(&y);  // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1);            // what the fuck?
    y = *reinterpret_cast<float*>(&i);
    y = y * (threehalfs - (x2 * y * y));  // 1st iteration
    // y  = y * (threehalfs - (x2 * y * y));  // 2nd iteration, this can be removed for less precision

    return 1 / y;
}

inline bool aproxEqual(double left, double right, double errorMargin) {
    return std::abs(left - right) < errorMargin;
}



#endif // !EXTRA_HPP
