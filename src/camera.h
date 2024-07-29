//
// Created by Kamil Tokarski on 28/07/2024.
//

#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include "rtow.h"
#include "material.h"

const auto PPM_HEADER = "P3\n";


class Camera {
    int image_height;
    Point3d center;
    Point3d pixel00_loc;
    Vec3d pixel_delta_u;
    Vec3d pixel_delta_v;

    double pixel_samples_scale;

    Vec3d u, v, w;

    void Initialize() {
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1 ? 1 : image_height);

        pixel_samples_scale = 1.0 / samples_per_pixel;
        center = camera_pos;

        const auto focal_length = (camera_pos - view_pos).Length();
        const auto theta = MathUtil::Deg2Rad(fov);
        const auto h = std::tan(theta/2);
        const auto view_height = 2 * h * focal_length;
        const auto view_width = view_height * (static_cast<double>(image_width) / (image_height));

        w = (camera_pos - view_pos).Unit();
        u = (VecUtil::Cross(vector_up, w)).Unit();
        v = VecUtil::Cross(w, u);

        const auto viewport_u = view_width * u;
        const auto viewport_v = view_height * -v;

        pixel_delta_u = viewport_u / static_cast<double>(image_width);
        pixel_delta_v = viewport_v / static_cast<double>(image_height);

        const auto view_corner = center - (focal_length * w) - viewport_u/2.0 - viewport_v/2.0;
        pixel00_loc = view_corner + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    Ray GetRay(int y, int x) {
        auto offset = VecUtil::RandomWindow();
        auto pixel_sample = pixel00_loc
                          + ((x + offset.x()) * pixel_delta_u)
                          + ((y + offset.y()) * pixel_delta_v);
        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        return Ray(ray_origin, ray_direction);
    }

    Color GetRayColor(const Ray& ray, const Hittable& world, const int depth = 0) {
        if (depth >= max_depth)
            return {0, 0, 0};

        if (HitRecord record; world.CheckHit(ray, Interval(0.001, MathUtil::INF), record)) {
            Ray scattered;
            Color attenuation;

            if (record.material->Scatter(ray, record, attenuation, scattered))
                return attenuation * GetRayColor(scattered, world, depth + 1);
            return {0, 0, 0};
        }

        const auto unit_dir = ray.direction().Unit();
        const auto alpha = (unit_dir.y() + 1.0) / 2.f;

        return (1.0 - alpha) * Color(1, 1, 1) + alpha * Color(0.5, 0.7, 1.0);
    }
public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 10;

    double fov = 90.f;

    Point3d camera_pos;
    Point3d view_pos;
    Vec3d vector_up;

    void Render(const Hittable& world, std::ofstream& file) {
        Initialize();

        auto progress_update = image_height / 10;
        auto progress = 0;
        std::cerr << "Render started" << std::endl;
        std::cerr << "[";
        file << PPM_HEADER << image_width << " " << image_height << "\n255\n";
        for (auto y = 0; y < image_height; ++y) {
            if (++progress == progress_update) {
                std::cerr << "+";
                progress = 0;
            }
            for(auto x = 0; x < image_width; ++x) {
                Color pixel_color(0, 0, 0);

                {
                    auto pixel =  pixel00_loc
                                             + (static_cast<double>(x) * pixel_delta_u)
                                             + (static_cast<double>(y) * pixel_delta_v);
                    auto direction = pixel - center;
                    Ray ray(center, direction);
                    pixel_color += GetRayColor(ray, world);
                }


                for(auto sample = 1; sample < samples_per_pixel; ++sample) {
                    auto ray = GetRay(y, x);
                    pixel_color += GetRayColor(ray, world);
                }

                file << pixel_color * pixel_samples_scale << "\n";
            }
        }

        std::cerr << "]\n";
        std::cerr << "Finished." << "\n";
    }
};

#endif //CAMERA_H
