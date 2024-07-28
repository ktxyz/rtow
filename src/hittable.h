//
// Created by Kamil Tokarski on 28/07/2024.
//

#ifndef HITTABLE_H
#define HITTABLE_H
#pragma once

#include "interval.h"
#include "ray.h"

class Material;

struct HitRecord {
    Point3d point;
    Vec3d normal;
    double offset;
    bool front_face;
    std::shared_ptr<Material> material;

    void set_face_normal(const Ray& ray, const Vec3d& out_normal) {
        front_face = VecUtil::Dot(ray.direction(), out_normal) < 0.0f;
        normal = front_face ? out_normal : -out_normal;
    }
};


class Hittable {
public:
    virtual ~Hittable() = default;
    virtual bool CheckHit(const Ray& ray, const Interval& interval, HitRecord& record) const = 0;
};

#endif //HITTABLE_H
