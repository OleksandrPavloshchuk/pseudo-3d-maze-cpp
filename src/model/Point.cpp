/**
 * Point.cpp
 */
 
#include <cmath>

constexpr double EPSILON = 1e-9;

bool areEqual(double a, double b) {
    return std::abs(a - b) < EPSILON;
}

