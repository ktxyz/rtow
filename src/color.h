//
// Created by Kamil Tokarski on 26/07/2024.
//

#ifndef COLOR_H
#define COLOR_H
#pragma once

#include "interval.h"


using Color = Vec3d;
constexpr double PPM_VALUE = 255.99;

inline double Linear2Gamma(const double linear_component) {
    if (linear_component > 0)
        return std::sqrt(linear_component);
    return 0;
}

template <typename Stream>
Stream& operator<<(Stream& out, const Color& col) {
    const auto r = Linear2Gamma(col.x());
    const auto g = Linear2Gamma(col.y());
    const auto b = Linear2Gamma(col.z());

    static const Interval intensity(0.000, 0.999);
    const int rbyte = static_cast<int>(256 * intensity.Clamp(r));
    const int gbyte = static_cast<int>(256 * intensity.Clamp(g));
    const int bbyte = static_cast<int>(256 * intensity.Clamp(b));

    out << rbyte << " " << gbyte << " " << bbyte;
    return out;
}


#endif //COLOR_H
