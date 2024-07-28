//
// Created by Kamil Tokarski on 26/07/2024.
//

#ifndef COLOR_H
#define COLOR_H
#pragma once

#include <fstream>

#include "hittable.h"

using Color = Vec3d;
constexpr double PPM_VALUE = 255.99;

inline Color GetRayColor(const Ray& ray, const Hittable& world) {
    if (HitRecord record; world.CheckHit(ray, Interval(0, MathUtil::INF), record))
        return 0.5 * (record.normal + Color(1, 1, 1));

    const auto unit_dir = ray.direction().unit();
    const auto alpha = (unit_dir.y() + 1.0) / 2.f;

    return (1.0 - alpha) * Color(1, 1, 1) + alpha * Color(0.5, 0.7, 1.0);
}

inline std::fstream& operator<<(std::fstream& out, const Color& col) {
    out << static_cast<int>(col.x() * PPM_VALUE) << " " <<
            static_cast<int>(col.y() * PPM_VALUE) << " " <<
            static_cast<int>(col.z() * PPM_VALUE);
    return out;
}

inline std::ostream& operator<<(std::ostream& out, const Color& col) {
    out << static_cast<int>(col.x() * PPM_VALUE) << " " <<
            static_cast<int>(col.y() * PPM_VALUE) << " " <<
            static_cast<int>(col.z() * PPM_VALUE);
    return out;
}

#endif //COLOR_H
