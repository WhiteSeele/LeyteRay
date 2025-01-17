//
// Created by $yujinxiang on 2025/1/15.
//

#include "common.h"
#include "camera.h"

#include "Hit.h"
#include "material.h"

void Camera::render(const Hittable &world) {
    initialize();

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for(int j = 0; j < image_height; j++) {
        for(int i = 0; i < image_width; i++) {
            Color pixel_color{0, 0, 0};
            for(int s = 0; s < samples_per_pixel; s++) {
                Ray r = getRay(i, j);
                pixel_color += rayColor(r, max_depth, world);
            }
            writeColor(pixel_color * samples_pixels_scale, i, j);
        }
    }
    stbi_write_png("image6.png", image_width, image_height, 3, frame_buffer.data(), image_width * 3);
    std::clog << "\rDone.        \n";
}


Color Camera::rayColor(const Ray &r, int depth, const Hittable &world) {
    if (depth <= 0) {
        return {0, 0, 0};
    }
    if (HitLoad rec; world.hit(r, Interval(0.001, INF), rec)) {
        Ray scattered;
        Color attenuation;
        if (rec.mat -> scatter(r, rec, attenuation, scattered)) {
            return attenuation * rayColor(scattered, depth - 1, world);
        }
        return {0, 0, 0};
    }
    Vec3 normal_dir = normalize(r.direction());
    auto a = 0.5 * (normal_dir.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

void Camera::initialize() {
    //Image
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1: image_height;

    frame_buffer.reserve(image_width * image_height * 3);
    samples_pixels_scale = 1.0 / samples_per_pixel;
    //Camera
    camera_center = Point3(0, 0, 0);
    //Viewport Dimensions
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    //Viewport 水平和垂直方向的向量
    auto viewport_u = Vec3(viewport_width, 0, 0);
    auto viewport_v = Vec3(0, -viewport_height, 0);

    //Viewport 水平和垂直方向的像素间隔
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = camera_center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    pixel00_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

void Camera::writeColor(const Color &pixel_color, int i, int j) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();
    static const Interval intensity(0.000, 0.999);   //0.999 处理精度问题
    r = gammaCorrection(r);
    g = gammaCorrection(g);
    b = gammaCorrection(b);

    int rByte = static_cast<int>(256 * intensity.clamp(r));
    int gByte = static_cast<int>(256 * intensity.clamp(g));
    int bByte = static_cast<int>(256 * intensity.clamp(b));

    int index = (j * image_width + i) * 3;
    frame_buffer[index] = static_cast<unsigned char>(rByte);
    frame_buffer[index + 1] = static_cast<unsigned char>(gByte);
    frame_buffer[index + 2] = static_cast<unsigned char>(bByte);
}

Ray Camera::getRay(int i, int j) const {
    auto offset = sampleSqure();
    auto samplePixel = pixel00_location + (i + offset.x()) * pixel_delta_u + (j + offset.y()) * pixel_delta_v;

    auto ray_origin = camera_center;
    auto ray_direction = samplePixel - camera_center;

    return Ray(ray_origin, ray_direction);
}

Vec3 Camera::sampleSqure() const {
    // return the vector to a random point in the [-0.5, 0.5] x [-0.5, 0.5] unit squre.
    return {randomDouble() - 0.5, randomDouble() - 0.5, 0};
}

double Camera::gammaCorrection(double color) const {
    if (color <= 0) {
        return 0;
    }
    return std::pow(color, 1.0 / 2.2);
}