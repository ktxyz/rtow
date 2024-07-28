//
// Created by Kamil Tokarski on 27/07/2024.
//

#ifndef SPHERE_H
#define SPHERE_H
#pragma once

#include <utility>

#include "hittable.h"


class Sphere : public Hittable {
    Point3d center;
    double radius;
    std::shared_ptr<Material> material;
public:
    Sphere(const Point3d& center, const double radius, std::shared_ptr<Material> material) : center(center),
                                                    radius(std::fmax(0, radius)), material(std::move(material)) {}

    bool CheckHit(const Ray &ray, const Interval& interval, HitRecord &record) const override {
        Vec3d oc = center - ray.origin();
        auto a = ray.direction().Length2();
        auto h = VecUtil::Dot(ray.direction(), oc);
        auto c = oc.Length2() - radius * radius;

        auto discriminant = h*h - a*c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        auto root = (h - sqrtd) / a;
        if (!interval.Surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!interval.Surrounds(root))
                return false;
        }

        record.offset = root;
        record.point = ray.Offset(record.offset);
        record.normal = (record.point - center) / radius;
        record.set_face_normal(ray, record.normal);
        record.material = material;

        return true;
    }
};

#endif //SPHERE_H
