//
// Created by $yujinxiang on 2025/1/14.
//

#ifndef HIT_H
#define HIT_H

#include "common.h"

class Material;

struct HitLoad {
    Point3 p;        //hit point
    Vec3 n;          //normal vector
    double t = 0.0;
    bool front_face;      // 判断光线从物体外来还是从物体内来
    shared_ptr<Material> mat;       //碰撞点的材质

    void set_face_normal(const Ray& r, const Vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        n = front_face ? outward_normal : -outward_normal;   //假定法线方向垂直于物体表面向外，光线从外来则法线方向不变，光线从内来则法线方向取反
    }
};

/*
    * Hittable class：定义光线与物体碰撞的函数接口
*/
class Hittable {
public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray& r, const Interval& tRay, HitLoad &rec) const = 0;

};

#endif //HIT_H
