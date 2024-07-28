//
// Created by Kamil Tokarski on 28/07/2024.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#pragma once

#include "rtow.h"

struct HitRecord;

class Material {
public:
    virtual ~Material() = default;

    virtual bool Scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const {
        return false;
    }
};

class MLambertian : public Material {
    Color albedo;
public:
    MLambertian(const Color& albedo) : albedo(albedo) {}

    bool Scatter(const Ray &ray, const HitRecord &record, Color &attenuation, Ray &scattered) const override {
        auto scatter_direction = record.normal + VecUtil::RandomUnitVec3d();

        if (scatter_direction.NearZero())
            scatter_direction = record.normal;

        scattered = Ray(record.point, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

class MMetal : public Material {
    double fuzz;
    Color albedo;
public:
    MMetal(Color albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool Scatter(const Ray &ray, const HitRecord &record, Color &attenuation, Ray &scattered) const override {
        auto reflected = VecUtil::ReflectVec3d(ray.direction(), record.normal);
        reflected = reflected.Unit() + fuzz * VecUtil::RandomUnitVec3d();

        scattered = Ray(record.point, reflected);
        attenuation = albedo;

        return VecUtil::Dot(scattered.direction(), record.normal) > 0;
    }
};

#endif //MATERIAL_H
