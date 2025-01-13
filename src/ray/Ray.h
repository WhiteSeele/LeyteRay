//
// Created by $yujinxiang on 2025/1/13.
//

#ifndef RAY_H
#define RAY_H
#include "Vec3.h"


class Ray {
public:
    Ray() {}
    Ray(const Point3& origin, const Vec3& dir): o(origin), dir(dir) {}

    [[nodiscard]] const Point3& origin() const {return o;}
    [[nodiscard]] const Vec3& direction() const {return dir; }

    Point3 at(double t) const {
        return o + t * dir;
    }

private:
    Point3 o;
    Vec3 dir;
};

#endif //RAY_H
