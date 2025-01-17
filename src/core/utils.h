//
// Created by yujinxiang on 2025/1/17.
//

#ifndef SAMPLE_H
#define SAMPLE_H

#include <random>

constexpr double INF = std::numeric_limits<double>::infinity();
constexpr double PI = 3.1415926535897932385;

inline double degreesToRadians(const double degrees) {
    return degrees * PI / 180.0;
}

inline double randomDouble() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double randomDouble(double min, double max) {
    return min + (max - min) * randomDouble();
}

#endif //SAMPLE_H
