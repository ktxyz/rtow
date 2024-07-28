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
    double val[3];
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

    T length() const { return std::sqrt(length2()); }
    T length2() const {
        return val[0] * val[0] + val[1] * val[1] + val[2] * val[2];
    }

    Vec3 unit() const {
        return *this / length();
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

#endif //VEC3_H
