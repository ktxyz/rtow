//
// Created by Kamil Tokarski on 26/07/2024.
//

#include "camera.h"


int main() {
    auto file = std::ofstream("output.ppm");

    auto material_ground = std::make_shared<MLambertian>(Color(0.8, 0.8, 0));
    auto material_center = std::make_shared<MLambertian>(Color(0.1, 0.2, 0.5));
    auto material_left   = std::make_shared<MMetal>(Color(0.8, 0.8, 0.8), 0.3);
    auto material_right  = std::make_shared<MMetal>(Color(0.8, 0.6, 0.2), 1);

    HittableList world;
    world.push_back(make_shared<Sphere>(Point3d( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.push_back(make_shared<Sphere>(Point3d( 0.0,    0.0, -1.2),   0.5, material_center));
    world.push_back(make_shared<Sphere>(Point3d(-1.0,    0.0, -1.0),   0.5, material_left));
    world.push_back(make_shared<Sphere>(Point3d( 1.0,    0.0, -1.0),   0.5, material_right));

    Camera camera;
    camera.aspect_ratio = 16.f / 9.f;
    camera.image_width = 1024;
    camera.samples_per_pixel = 64;
    camera.max_depth = 10;

    camera.Render(world, file);

    return 0;
}
