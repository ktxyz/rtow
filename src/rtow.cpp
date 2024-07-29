//
// Created by Kamil Tokarski on 26/07/2024.
//

#include "camera.h"


int main() {
    auto file = std::ofstream("output.ppm");

    auto material_ground = std::make_shared<MLambertian>(Color(0.8, 0.8, 0));
    auto material_center = std::make_shared<MLambertian>(Color(0.1, 0.2, 0.5));
    auto material_left   = std::make_shared<MDielectric>(1.50);
    auto material_bubble = std::make_shared<MDielectric>(1.00 / 1.50);
    auto material_right  = std::make_shared<MMetal>(Color(0.8, 0.6, 0.2), 1);

    HittableList world;
    world.push_back(std::make_shared<Sphere>(Point3d( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.push_back(std::make_shared<Sphere>(Point3d( 0.0,    0.0, -1.2),   0.5, material_center));
    world.push_back(std::make_shared<Sphere>(Point3d(-1.0,    0.0, -1.0),   0.5, material_left));
    world.push_back(std::make_shared<Sphere>(Point3d(-1.0,    0.0, -1.0),   0.4, material_bubble));
    world.push_back(std::make_shared<Sphere>(Point3d( 1.0,    0.0, -1.0),   0.5, material_right));

    Camera camera;
    camera.aspect_ratio = 16.f / 9.f;
    camera.image_width = 400;
    camera.samples_per_pixel = 32;
    camera.max_depth = 10;
    camera.fov = 20;
    camera.camera_pos = Point3d(-2, 2, 1);
    camera.view_pos = Point3d(0, 0, -1);
    camera.vector_up = Vec3d(0, 1, 0);

    camera.defocus_angle = 10;
    camera.focus_distance = 3.4;

    camera.Render(world, file);

    return 0;
}
