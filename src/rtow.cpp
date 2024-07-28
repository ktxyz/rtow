//
// Created by Kamil Tokarski on 26/07/2024.
//


#include "camera.h"


int main() {
    auto file = std::ofstream("output.ppm");

    HittableList world;
    world.push_back(std::make_shared<Sphere>(Point3d(0, 0, -1), 0.5));
    world.push_back(std::make_shared<Sphere>(Point3d(0, -100.5, -1), 100));

    Camera camera;
    camera.aspect_ratio = 16.f / 9.f;
    camera.image_width = 1024;

    camera.Render(world, file);

    return 0;
}
