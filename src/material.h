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

class MLambertian final : public Material {
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

class MMetal final : public Material {
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

class MDielectric final : public Material {
    double refraction_index;

    static double Reflectance(double cosine, double refraction_index) {
        auto r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 *= r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }

public:
    MDielectric(double refraction_index) : refraction_index(refraction_index) {}

    bool Scatter(const Ray &ray, const HitRecord &record, Color &attenuation, Ray &scattered) const override {
        attenuation = Color(1, 1, 1);
        const auto ri = (record.front_face ? (1.0 / refraction_index) : refraction_index);

        const auto unit_dir = ray.direction().Unit();
        const auto cos_theta = std::fmin(VecUtil::Dot(-unit_dir, record.normal), 1.0);
        const auto sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

        if ((ri * sin_theta > 1.0) || Reflectance(cos_theta, ri) > MathUtil::RandomDouble()) {
            const auto reflected = VecUtil::ReflectVec3d(unit_dir, record.normal);
            scattered = Ray(record.point, reflected);
        } else {
            const auto refracted = VecUtil::Refract(unit_dir, record.normal, ri);
            scattered = Ray(record.point, refracted);
        }

        return true;
    }
};

#endif //MATERIAL_H
