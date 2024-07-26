//
// Created by Kamil Tokarski on 27/07/2024.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "ray.h"

struct Sphere {
    Point3d center;
    double radius;

    bool is_hit(const Ray& ray) const {
        const auto oc = center - ray.origin();

        const auto a = Vec3Util::dot(ray.direction(), ray.direction());
        const auto b = -2.0 * Vec3Util::dot(ray.direction(), oc);
        const auto c = Vec3Util::dot(oc, oc) - radius * radius;

        const auto discriminant = (b * b) - (4 * a * c);
        return discriminant >= 0;
    }
};

#endif //SPHERE_H
