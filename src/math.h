//
// Created by Kamil Tokarski on 28/07/2024.
//

#ifndef MATH_H
#define MATH_H
#pragma once

#include <limits>
#include <memory>
#include <random>

#include "vec3.h"


namespace MathUtil {
    const auto INF = std::numeric_limits<double>::infinity();
    constexpr double PI = 3.1415926535897932385;

    inline double Deg2Rad(const double degrees) {
        return degrees * PI / 180.0;
    }

    inline double RandomDouble() {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    inline Vec3d RandomWindow(const double window_size = 0.5) {
        return {RandomDouble() - window_size, RandomDouble() - window_size, 0};
    }

    template<typename T>
    T dot(const Vec3<T>& v1, const Vec3<T>& v2) {
        return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
    }

    template<typename T>
    Vec3<T> cross(const Vec3<T>& v1, const Vec3<T>& v2) {
        return {
            v1.x() * v2.z() - v1.z() * v2.x(),
            v1.z() * v2.x() - v1.x() * v2.z(),
            v1.x() * v2.y() - v1.y() * v2.x(),
        };
    }
}

#endif //MATH_H
