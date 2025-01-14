//
// Created by $yujinxiang on 2025/1/14.
//

#include "HittableList.h"

HittableList::HittableList(const std::initializer_list<shared_ptr<Hittable>> list) {
    for (auto& obj: list) {
        add(obj);
    }
}

void HittableList::add(const shared_ptr<Hittable>& object) {
    objects.push_back(object);
}

void HittableList::clear() {
    objects.clear();
}


bool HittableList::hit(const Ray &r, const Interval &tRay, HitLoad &rec) const {
    HitLoad temp_rec;
    bool hit_anything = false;
    double closest_so_far = tRay.max;

    for (const auto& object: objects) {
        if (object->hit(r, Interval(tRay.min, closest_so_far), temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}