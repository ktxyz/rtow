//
// Created by Kamil Tokarski on 26/07/2024.
//

#include "camera.h"


int main() {
    auto file = std::ofstream("output.ppm");

    HittableList world;

    auto ground_material = std::make_shared<MLambertian>(Color(0.5, 0.5, 0.5));
    world.push_back(std::make_shared<Sphere>(Point3d(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = MathUtil::RandomDouble();
            Point3d center(a + 0.9*MathUtil::RandomDouble(), 0.2, b + 0.9*MathUtil::RandomDouble());

            if ((center - Point3d(4, 0.2, 0)).Length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = ColorUtils::RandomColor();
                    sphere_material = std::make_shared<MLambertian>(albedo);
                    world.push_back(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = ColorUtils::RandomColor(0.5, 1);
                    auto fuzz = MathUtil::RandomDouble(0, 0.5);
                    sphere_material = std::make_shared<MMetal>(albedo, fuzz);
                    world.push_back(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<MDielectric>(1.5);
                    world.push_back(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<MDielectric>(1.5);
    world.push_back(make_shared<Sphere>(Point3d(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<MLambertian>(Color(0.4, 0.2, 0.1));
    world.push_back(std::make_shared<Sphere>(Point3d(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<MMetal>(Color(0.7, 0.6, 0.5), 0.0);
    world.push_back(std::make_shared<Sphere>(Point3d(4, 1, 0), 1.0, material3));

    Camera camera;

    camera.aspect_ratio      = 16.0 / 9.0;
    camera.image_width       = 1620;
    camera.samples_per_pixel = 500;
    camera.max_depth         = 50;

    camera.fov     = 20;
    camera.camera_pos = Point3d(13,2,3);
    camera.view_pos   = Point3d(0,0,0);
    camera.vector_up      = Point3d(0,1,0);

    camera.defocus_angle = 0.6;
    camera.focus_distance    = 10.0;

    camera.Render(world, file);

    return 0;
}
