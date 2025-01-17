//
// Created by yujinxiang on 2025/1/15.
//

/*
 * Camera Class:
 * Construct and dispatch rays into the world.
 * Use the results of these rays to construct the rendered image.
 */

#ifndef CAMERA_H
#define CAMERA_H
#include "common.h"


class Ray;
class Hittable;

class Camera {
public:
    double aspect_ratio = 1.0;   //宽高比
    int image_width = 100;       //Rendered Image width in pixel count
    int samples_per_pixel = 10;   //Number of samples per pixel
    int max_depth = 10;          //Maximum depth of ray bounces into scene
    void render(const Hittable& world);

private:
    int image_height;
    double samples_pixels_scale;
    Point3 camera_center;
    Point3 pixel00_location;
    Point3 pixel_delta_u;
    Point3 pixel_delta_v;

    std::vector<unsigned char> frame_buffer;

    void initialize();

    void writeColor(const Color& pixel_color, int i, int j);

    Color rayColor(const Ray& r, int depth, const Hittable& world);

    /*
     * Construct a camera ray originating from the origin and directed at randomly sampled point around the pixel location i, j.
     */
    [[nodiscard]] Ray getRay(int i, int j) const;

    [[nodiscard]] Vec3 sampleSqure() const;

    [[nodiscard]] double gammaCorrection(double color) const;
};



#endif //CAMERA_H
