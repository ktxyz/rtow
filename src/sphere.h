//
// Created by Kamil Tokarski on 27/07/2024.
//

#ifndef SPHERE_H
#define SPHERE_H
#pragma once

#include "hittable.h"


class Sphere : public Hittable {
    Point3d center;
    double radius;
public:
    Sphere(const Point3d& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

    bool CheckHit(const Ray &ray, const Interval& interval, HitRecord &record) const override {
        Vec3d oc = center - ray.origin();
        auto a = ray.direction().length2();
        auto h = MathUtil::dot(ray.direction(), oc);
        auto c = oc.length2() - radius * radius;

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

        return true;
    }
};

#endif //SPHERE_H
