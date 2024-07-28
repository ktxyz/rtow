//
// Created by Kamil Tokarski on 28/07/2024.
//

#ifndef MATH_H
#define MATH_H
#pragma once

#include <limits>
#include <memory>
#include <random>

namespace MathUtil {
    const auto INF = std::numeric_limits<double>::infinity();
    constexpr double PI = 3.1415926535897932385;
    constexpr double EPSILON = 1e-8;

    inline double Deg2Rad(const double degrees) {
        return degrees * PI / 180.0;
    }

    inline double RandomDouble(double min = 0.0, double max = 1.0) {
        static std::mt19937 generator;

        std::uniform_real_distribution<double> distribution(min, max);
        return distribution(generator);
    }
}

#endif //MATH_H
