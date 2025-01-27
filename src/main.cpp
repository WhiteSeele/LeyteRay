#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <chrono>

#include "camera.h"
#include "Hit.h"
#include "HittableList.h"
#include "material.h"
#include "Sphere.h"
#include "TimerProfile.h"


int main() {
    TimerProfile timer;
    //Material
    auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Dielectric>(1.50);
    auto material_bubble = make_shared<Dielectric>(1.00 / 1.50);
    auto material_right  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.8);


    //World
    HittableList world;
    // world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    // world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));
    world.add(make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(Point3( 0.0, 0.0, -1.2),   0.5, material_center));
    world.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0),   0.5, material_left));
    world.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0),   0.4, material_bubble));
    world.add(make_shared<Sphere>(Point3( 1.0, 0.0, -1.0),   0.5, material_right));

    //Camera
    Camera camera;
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 1920;
    camera.samples_per_pixel = 25;
    camera.max_depth = 50;
    //Render
    timer.start();
    camera.render(world);
    timer.end();

    return 0;
}
