//
// Created by Kamil Tokarski on 26/07/2024.
//

#ifndef VEC3_H
#define VEC3_H
#pragma once

#include <cmath>
#include <ostream>


template<typename T>
class Vec3 {
    static constexpr int SIZE = 3;
    T val[3]{};
public:
    Vec3() : val{0, 0, 0} {}
    Vec3(T x, T y, T z) : val{x, y, z} {}

    T x() const { return val[0]; }
    T x(T value) { return val[0] = value; }

    T y() const { return val[1]; }
    T y(T value) { return val[1] = value; }

    T z() const { return val[2]; }
    T z(T value) { return val[2] = value; }

    Vec3 operator-() const { return {-val[0], -val[1], -val[2]}; }
    T operator[](const size_t i) const { return val[i]; }
    T& operator[](const size_t i) { return val[i]; }

    Vec3 operator+=(const Vec3& other) {
        for(auto i = 0; i < SIZE; ++i)
            val[i] += other.val[i];
        return *this;
    }
    Vec3 operator*=(const T value) {
        for(double &i : val)
            i *= value;
        return *this;
    }
    Vec3 operator/=(const T value) { return *this *= (1 / value); }

    T Length() const { return std::sqrt(Length2()); }
    T Length2() const {
        return val[0] * val[0] + val[1] * val[1] + val[2] * val[2];
    }

    Vec3 Unit() const {
        return *this / Length();
    }

    bool NearZero() const {
        for(const auto &value : val)
            if (std::fabs(value) > MathUtil::EPSILON)
                return false;
        return true;
    }
};

using Vec3d = Vec3<double>;
using Point3d = Vec3d;

template<typename T>
std::ostream& operator<<(std::ostream& out, const Vec3<T>& v) {
    return out << "[" << v.x() << "; " << v.y() << "; " << v.z() << "]";
}

template<typename T>
Vec3<T> operator+(const Vec3<T>& v1, const Vec3<T>& v2) {
    return {v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z()};
}

template<typename T>
Vec3<T> operator-(const Vec3<T>& v1, const Vec3<T>& v2) {
    return {v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z()};
}

template<typename T>
Vec3<T> operator*(const Vec3<T>& v1, const Vec3<T>& v2) {
    return {v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z()};
}

template<typename T>
Vec3<T> operator*(T value, const Vec3<T>& v1) {
    return {v1.x() * value, v1.y() * value, v1.z() * value};
}

template<typename T>
Vec3<T> operator*(const Vec3<T>& v1, T value) {
    return value * v1;
}

template<typename T>
Vec3<T> operator/(const Vec3<T>& v1, T value) {
    return v1 * (1.0 / value);
}

namespace VecUtil {
    inline Vec3d RandomWindow(const double window_size = 0.5) {
        return {MathUtil::RandomDouble() - window_size, MathUtil::RandomDouble() - window_size, 0};
    }

    inline Vec3d RandomVec3d(const double min = 0.f, const double max = 1.f) {
        return {MathUtil::RandomDouble(min, max), MathUtil::RandomDouble(min, max), MathUtil::RandomDouble(min, max)};
    }

    inline Vec3d RandomUnitVec3d() {
        while (true)
            if (auto p = RandomVec3d(-1, 1); p.Length2() < 1)
                return p.Unit();
    }

    template<typename T>
    T Dot(const Vec3<T>& v1, const Vec3<T>& v2) {
        return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
    }

    template<typename T>
    Vec3<T> Cross(const Vec3<T>& v1, const Vec3<T>& v2) {
        return {
            v1.x() * v2.z() - v1.z() * v2.x(),
            v1.z() * v2.x() - v1.x() * v2.z(),
            v1.x() * v2.y() - v1.y() * v2.x(),
        };
    }

    inline Vec3d RandomVec3dHemisphere(const Vec3d& normal) {
        const auto unit_vec = RandomUnitVec3d();
        if (Dot(unit_vec, normal) > 0.0)
            return unit_vec;
        return -unit_vec;
    }

    inline Vec3d ReflectVec3d(const Vec3d& vec, const Vec3d& origin) {
        return vec - 2 * Dot(vec, origin) * origin;
    }
}

#endif //VEC3_H
