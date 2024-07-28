//
// Created by Kamil Tokarski on 28/07/2024.
//

#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include "rtow.h"

const auto PPM_HEADER = "P3\n";


class Camera {
    int image_height;
    Point3d center;
    Point3d pixel00_loc;
    Vec3d pixel_delta_u;
    Vec3d pixel_delta_v;

    void Initialize() {
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1 ? 1 : image_height);

        center = Point3d(0, 0, 0);

        constexpr auto focal_length = 1.0;
        constexpr auto view_height = 2.0;
        const auto view_width = view_height * (static_cast<double>(image_width) / (image_height));

        const auto viewport_u = Vec3d(view_width, 0, 0);
        const auto viewport_v = Vec3d(0, -view_height, 0);

        pixel_delta_u = viewport_u / static_cast<double>(image_width);
        pixel_delta_v = viewport_v / static_cast<double>(image_height);

        const auto view_corner = center - Vec3d(0, 0, focal_length)
                                       - viewport_u / 2.0 - viewport_v / 2.0;
        pixel00_loc = view_corner + 0.5 * (pixel_delta_u + pixel_delta_v);
    }


    static Color GetRayColor(const Ray& ray, const Hittable& world) {
        if (HitRecord record; world.CheckHit(ray, Interval(0, MathUtil::INF), record))
            return 0.5 * (record.normal + Color(1, 1, 1));

        const auto unit_dir = ray.direction().unit();
        const auto alpha = (unit_dir.y() + 1.0) / 2.f;

        return (1.0 - alpha) * Color(1, 1, 1) + alpha * Color(0.5, 0.7, 1.0);
    }
public:
    double aspect_ratio = 1.0;
    int image_width = 100;

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
                auto pixel =  pixel00_loc
                                          + (static_cast<double>(x) * pixel_delta_u)
                                          + (static_cast<double>(y) * pixel_delta_v);
                auto direction = pixel - center;
                Ray ray(center, direction);

                file << GetRayColor(ray, world) << "\n";
            }
        }
        std::cerr << "]\n";

        std::cerr << "Finished." << "\n";
    }
};

#endif //CAMERA_H
