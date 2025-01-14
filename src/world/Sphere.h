//
// Created by $yujinxiang on 2025/1/14.
//

#ifndef SPHERE_H
#define SPHERE_H
#include "../math/Vec3.h"
#include "Hit.h"


class Ray;

class Sphere : public Hittable {
public:
    Sphere(const Point3& center, double radius) : center(center), radius(radius) {}

    bool hit(const Ray& r, const Interval& tRay, HitLoad& rec) const override;

private:
    Point3 center;
    double radius;
};



#endif //SPHERE_H
