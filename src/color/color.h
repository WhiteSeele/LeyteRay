//
// Created by yujingxiang on 2025/1/13.
//

#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "Vec3.h"

using Color = Vec3;

inline void write_color(std::ostream &out, const Color& pixel_color) {
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

#endif //COLOR_H
