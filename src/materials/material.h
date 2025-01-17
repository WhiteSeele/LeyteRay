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

#endif //MATERIAL_H
