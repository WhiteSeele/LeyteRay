//
// Created by yujinxiang on 2025/1/17.
//

#ifndef METAL_H
#define METAL_H
#include "Material.h"
#include "Vec3.h"

class Metal: public Material {
public:
    explicit Metal(const Color& albedo): albedo(albedo) {}
    Metal(const Color& albedo, const double fuzz): albedo(albedo), fuzz(fuzz < 1.0 ? fuzz: 1.0) {}

    bool scatter(const Ray& r, const HitLoad& rec, Color& attenuation, Ray& scattered) const override{
        Vec3 reflected = mirrorReflect(r.direction(), rec.n);
        /**
         * In order for the fuzz sphere to make sense, it needs to be consistently scaled compared to the reflection vector,
         * which can vary in length arbitrarily. To address this, we need to normalize the reflected ray.
         */
        reflected = normalize(reflected) + fuzz * randomUnitVector();
        scattered = Ray(rec.p, reflected);
        attenuation = albedo;
        return dot(scattered.direction(), rec.n) > 0;
    }
private:
    Color albedo;
    double fuzz = 0.0;        //fuzz reflection, 介于完全的漫反射和完全的镜面反射之间，值越小越广滑
};

#endif //METAL_H
