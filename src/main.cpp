#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "common.h"
#include "Hit.h"
#include "HittableList.h"
#include "Sphere.h"

Color ray_color(const Ray& r, const Hittable& world) {
    HitLoad rec;
    if (world.hit(r, Interval(0, INF), rec)) {
        return 0.5 * (rec.n + Color(1, 1, 1));
    }
    Vec3 normal_dir = normalize(r.direction());
    auto a = 0.5 * (normal_dir.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main() {
    //Image
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 1920;
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1: image_height;

    //World
    HittableList world;

    world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    //Camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    auto camera_center = Point3(0, 0, 0);

    auto viewport_u = Vec3(viewport_width, 0, 0);
    auto viewport_v = Vec3(0, -viewport_height, 0);

    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = camera_center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    //Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    std::vector<unsigned char> image(image_width * image_height * 3);
    for(int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << image_height - j << std::flush;
        for(int i = 0; i < image_width; i++) {
            Point3 pixel_center = pixel00_location + (i * pixel_delta_u) + (j * pixel_delta_v);
            Vec3 ray_direction = pixel_center - camera_center;

            Ray r(camera_center, ray_direction);
            Color pixel_color = ray_color(r, world);
            int index = (j * image_width + i) * 3;
            image[index] = static_cast<unsigned char>(255.999 * pixel_color.x());
            image[index + 1] = static_cast<unsigned char>(255.999 * pixel_color.y());
            image[index + 2] = static_cast<unsigned char>(255.999 * pixel_color.z());
        }
    }
    stbi_write_png("image.png", image_width, image_height, 3, image.data(), image_width * 3);
    std::clog << "\rDone.        \n";
    return 0;

}
