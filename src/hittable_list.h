//
// Created by Kamil Tokarski on 28/07/2024.
//

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <utility>
#include <vector>

#include "hittable.h"


class HittableList : public Hittable {
    std::vector<std::shared_ptr<Hittable>> objects;

public:
    HittableList() = default;
    explicit HittableList(const std::shared_ptr<Hittable>& object) { push_back(object); }

    void push_back(const std::shared_ptr<Hittable>& object) {
        objects.emplace_back(object);
    }

    bool CheckHit(const Ray &ray, const Interval& interval, HitRecord &record) const override {
        HitRecord tmp_record;
        bool hit_anything = false;
        auto closest_so_far = interval.max;

        for(const auto& object : objects) {
            if (object->CheckHit(ray, interval, tmp_record)) {
                hit_anything = true;

                if (tmp_record.offset <= closest_so_far) {
                    closest_so_far = tmp_record.offset;
                    record = tmp_record;
                }
            }
        }

        return hit_anything;
    }
};

#endif //HITTABLE_LIST_H
