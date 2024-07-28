//
// Created by Kamil Tokarski on 26/07/2024.
//

#ifndef RAY_H
#define RAY_H
#pragma once

#include "vec3.h"


class Ray {
    Point3d orig;
    Vec3d dir;

public:
    Ray() = default;
    Ray(const Point3d& orig, const Vec3d& dir) : orig(orig), dir(dir) {}

    const Point3d& origin() const { return orig; }
    const Vec3d& direction() const { return dir; }

    Point3d Offset(const double offset) const {
        return orig + (offset * dir);
    }
};

#endif //RAY_H
