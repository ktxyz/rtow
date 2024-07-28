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

    inline double RandomDouble(double min = 0.0, double max = 1.0) {
        static std::mt19937 generator;

        std::uniform_real_distribution<double> distribution(min, max);
        return distribution(generator);
    }

    inline Vec3d RandomWindow(const double window_size = 0.5) {
        return {RandomDouble() - window_size, RandomDouble() - window_size, 0};
    }

    inline Vec3d RandomVec3d(const double min = 0.f, const double max = 1.f) {
        return {RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max)};
    }

    inline Vec3d RandomUnitVec3d() {
        while (true)
            if (auto p = RandomVec3d(-1, 1); p.length2() < 1)
                return p.unit();
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

    inline Vec3d RandomVec3dHemisphere(const Vec3d& normal) {
        const auto unit_vec = RandomUnitVec3d();
        if (dot(unit_vec, normal) > 0.0)
            return unit_vec;
        return -unit_vec;
    }
}

#endif //MATH_H
