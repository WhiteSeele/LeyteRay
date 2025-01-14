//
// Created by $yujinxiang on 2025/1/14.
//

#include "Sphere.h"
#include "../ray/Ray.h"

bool Sphere::hit(const Ray &r, const Interval &tRay, HitLoad &rec) const {
    Vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto h = dot(r.direction(), oc);          //b = -2h
    auto c = dot(oc, oc) - radius * radius;
    double delta = h * h -  a * c;

    if (delta < 0)
        return false;

    double sqrtd = std::sqrt(delta);
    double root = (h - sqrtd) / a;

    if (!tRay.surround(root)) {
        root = (h + sqrtd) / a;
        if (!tRay.surround(root))
            return false;
    }

    rec.t = root;
    rec.p = r.at(root);
    Vec3 outwardNormal = (rec.p - center) / radius;
    rec.set_face_normal(r, outwardNormal);

    return true;
}
