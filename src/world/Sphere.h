//
// Created by $yujinxiang on 2025/1/14.
//

#ifndef SPHERE_H
#define SPHERE_H
#include "Vec3.h"
#include "Hit.h"
#include "Ray.h"


class Ray;

class Sphere : public Hittable {
public:
    Sphere(const Point3& center, const double radius) : center(center), radius(std::fmax(0.0, radius)){}
    Sphere(const Point3& center, const double radius, const shared_ptr<Material> &mat) : center(center), radius(std::fmax(0.0, radius)), mat(mat) {}

    bool hit(const Ray& r, const Interval& tRay, HitLoad& rec) const override;

private:
    Point3 center;
    double radius;
    shared_ptr<Material> mat;
};



#endif //SPHERE_H
