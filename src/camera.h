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

    double fov = 90.0;           //Field of view in degrees
    Point3 lookfrom = Point3(0, 0, 0);
    Point3 lookat = Point3(0, 0, -1);
    Vec3 vup = Vec3(0, 1, 0);     // Camera-relative "up" direction

    double defocus_angle = 0.0;         // Variation angle of rays through each pixel
    double focus_distance = 10.0;           // Distance from camera lookfrom point to plane of perfect focus


    void render(const Hittable& world);

private:
    int image_height;              //Rendered Image height in pixel count
    double samples_pixels_scale;   //Color scale factor for a sum of each pixel samples
    Point3 camera_center;          //Camera center location
    Point3 pixel00_location;       //Location of pixel 0, 0
    Point3 pixel_delta_u;          //Offset to pixel to the right
    Point3 pixel_delta_v;          //Offset to pixel below
    Vec3 u, v, w;                  //camera frame basis vectors
    Vec3 defocus_disk_u;           //Defocus disk horizontal radius
    Vec3 defocus_disk_v;           //Defocus disk vertical radius

    std::vector<unsigned char> frame_buffer;

    void initialize();

    void writeColor(const Color& pixel_color, int i, int j);

    Color rayColor(const Ray& r, int depth, const Hittable& world);

    [[nodiscard]] Point3 defocus_disk_sample() const;

    /*
     * Construct a camera ray originating from the origin and directed at randomly sampled point around the pixel location i, j.
     */
    [[nodiscard]] Ray getRay(int i, int j) const;

    [[nodiscard]] Vec3 sampleSqure() const;

    [[nodiscard]] double gammaCorrection(double color) const;
};



#endif //CAMERA_H
