//
// Created by $yujinxiang on 2025/1/14.
//

#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include "common.h"
#include "Hit.h"

#include <memory>
#include <vector>


class HittableList : public Hittable {
public:
    HittableList() = default;
    explicit HittableList(const shared_ptr<Hittable>& object) { add(object); }
    HittableList(std::initializer_list<shared_ptr<Hittable>> list);

    void add(const shared_ptr<Hittable>& object);
    void clear();

    /*
     * 判断光线是否与列表中的物体相交, 如果有相交的物体返回true；
     * param:
     * @r: 光线
     * @t_min: 相交区间最小值
     * @t_max: 相交区间最大值
     * @rec: 光线与物体相交时的信息载体
     */
    bool hit(const Ray& r, const Interval &tRay, HitLoad &rec) const override;

private:
    std::vector<shared_ptr<Hittable>> objects;
};



#endif //HITTABLELIST_H
