//
// Created by $yujinxiang on 2025/1/14.
//

#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

using std::make_shared;
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;

constexpr double INF = std::numeric_limits<double>::infinity();
constexpr double PI = 3.1415926535897932385;

inline double degreesToRadians(const double degrees) {
    return degrees * PI / 180.0;
}

#include "Color.h"
#include "Ray.h"
#include "Vec3.h"
#include "stb_image_write.h"
#include "Interval.h"

#endif //COMMON_H
