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
