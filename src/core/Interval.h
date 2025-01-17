//
// Created by $yujinxiang on 2025/1/14.
//

#ifndef INTERVAL_H
#define INTERVAL_H

#include "common.h"

class Interval {
public:
    double min, max;

    /*
     * 默认区间
     */
    Interval() : min(INF), max(-INF) {}

    Interval(double min, double max): min(min), max(max) {}

    [[nodiscard]] double size() const {
        return max - min + 1;
    }

    [[nodiscard]] bool contains(double x) const {
        return x >= min && x <= max;
    }

    [[nodiscard]] bool surround(double x) const {
        return x > min && x < max;
    }

    [[nodiscard]] double clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static Interval empty() {
        return {INF, -INF};
    }

    static Interval universe() {
        return {-INF, INF};
    }
};

#endif //INTERVAL_H
