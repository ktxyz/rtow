//
// Created by Kamil Tokarski on 26/07/2024.
//

#include <fstream>
#include <iostream>

#include "rtow.h"


auto PPM_HEADER = "P3\n";

struct Camera {
    Point3d center;

    double view_height;
    double view_width;

    double focal_length;

    Vec3d viewport_u;
    Vec3d viewport_v;
};

int main() {
    auto file = std::ofstream("output.ppm");

    constexpr float ASPECT_RATIO = 16.f / 9.f;
    constexpr int WIDTH = 360;
    constexpr int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);

    HittableList world;
    world.push_back(std::make_shared<Sphere>(Point3d(0, 0, -1), 0.5));
    world.push_back(std::make_shared<Sphere>(Point3d(0, -100.5, -1), 100));

    Camera camera{};
    camera.center = Point3d(0, 0, 0);
    camera.focal_length = 1.0;
    camera.view_height = 2.0;
    camera.view_width = camera.view_height * (static_cast<double>(WIDTH) / (HEIGHT));

    camera.viewport_u = Vec3d(camera.view_width, 0, 0);
    camera.viewport_v = Vec3d(0, -camera.view_height, 0);

    const auto pixel_delta_u = camera.viewport_u / static_cast<double>(WIDTH);
    const auto pixel_delta_v = camera.viewport_v / static_cast<double>(HEIGHT);

    const auto view_corner = camera.center - Vec3d(0, 0, camera.focal_length)
                                   - camera.viewport_u / 2.0 - camera.viewport_v / 2.0;
    const auto pixel00_loc = view_corner + 0.5 * (pixel_delta_u + pixel_delta_v);


    file << PPM_HEADER << WIDTH << " " << HEIGHT << "\n255\n";
    for (auto y = 0; y < HEIGHT; ++y) {
        std::cerr << "Scanlines remaining: " << (HEIGHT - y) << "\n";
        for(auto x = 0; x < WIDTH; ++x) {
            auto pixel =  pixel00_loc
                                      + (static_cast<double>(x) * pixel_delta_u)
                                      + (static_cast<double>(y) * pixel_delta_v);
            auto direction = pixel - camera.center;
            Ray ray(camera.center, direction);

            file << GetRayColor(ray, world) << "\n";
        }
    }

    std::cerr << "Finished." << "\n";

    return 0;
}
