#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <chrono>

#include "camera.h"
#include "Hit.h"
#include "HittableList.h"
#include "Sphere.h"
#include "TimerProfile.h"


int main() {
    TimerProfile timer;
    //World
    HittableList world;
    world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    //Camera
    Camera camera;
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 1920;
    camera.samples_per_pixel = 25;
    camera.max_depth = 3;
    //Render
    timer.start();
    camera.render(world);
    timer.end();

    return 0;
}
