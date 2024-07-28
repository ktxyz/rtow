//
// Created by Kamil Tokarski on 28/07/2024.
//

#ifndef INTERVAL_H
#define INTERVAL_H
#pragma once

#include "math.h"


class Interval {
public:
    double min, max;

    Interval() : min(-MathUtil::INF), max(-MathUtil::INF) {}
    Interval(const double min, const double max) : min(min), max(max) {}

    double Length() const { return max - min; }
    bool Contains(const double point) const { return point >= min && point <= max; }
    bool Surrounds(const double point) const { return point > min && point < max; }

    static const Interval empty, universe;
};

const Interval Interval::empty = Interval(+MathUtil::INF, -MathUtil::INF);
const Interval Interval::universe = Interval(-MathUtil::INF, MathUtil::INF);

#endif //INTERVAL_H
