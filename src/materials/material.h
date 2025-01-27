//
// Created by yujinxiang on 2025/1/17.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Hit.h"


/**
 * Material class: Define the interface for scattering light.
 * The Material class needs to do two things:
 *  Produce a scattered ray (or say it absorbed the incident ray).
 *  If scattered, say how much the ray should be attenuated.
 */
class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& r_in, const HitLoad& rec, Color& attenuation, Ray& scattered) const {
        return false;
    }

};

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

class Metal: public Material {
public:
    explicit Metal(const Color& albedo): albedo(albedo) {}
    Metal(const Color& albedo, const double fuzz): albedo(albedo), fuzz(fuzz < 1.0 ? fuzz: 1.0) {}

    bool scatter(const Ray& r, const HitLoad& rec, Color& attenuation, Ray& scattered) const override{
        Vec3 reflected = reflect(r.direction(), rec.n);
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

class Dielectric: public Material {
public:
    explicit Dielectric(double ir): refraction_index(ir) {}

    bool scatter(const Ray& r, const HitLoad& rec, Color& attenuation, Ray& scattered) const override {
        attenuation = Color(1.0, 1.0, 1.0);
        double refraction_ratio = rec.front_face ? (1.0 / refraction_index) : refraction_index;

        Vec3 in_ray_udir = normalize(r.direction());

        double cos_theta = std::fmin(dot(-in_ray_udir, rec.n), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        Vec3 direction;

        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > randomDouble()) {
            direction = reflect(in_ray_udir, rec.n);
        } else {
            direction = refract(in_ray_udir, rec.n, refraction_ratio);
        }

        scattered = Ray(rec.p, direction);
        return true;
    }

private:
    double refraction_index;      //index of refraction

    static double reflectance(double cosine, double refraction_idx) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - refraction_idx) / (1 + refraction_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }
};

#endif //MATERIAL_H
