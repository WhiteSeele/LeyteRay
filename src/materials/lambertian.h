//
// Created by yujinxiang on 2025/1/17.
//

#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

class Lambertian : public Material {
public:
    explicit Lambertian(const Color& a) : albedo(a) {}

    bool scatter(const Ray& r, const HitLoad& rec, Color& attenuation, Ray& scattered) const override {
        auto scatter_direction = rec.n + randomUnitVector();

        if (scatter_direction.nearZero()) {
            scatter_direction = rec.n;
        }

        scattered = Ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

private:
    Color albedo;
};
#endif //LAMBERTIAN_H
