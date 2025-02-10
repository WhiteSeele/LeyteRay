//
// Created by yujingxiang on 2024/12/10.
//

#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include "utils.h"

class Vec3 {
public:
    double v[3];

    Vec3() : v{0, 0, 0} {}
    Vec3(double x, double y, double z) : v{x, y, z} {}

    [[nodiscard]] double x() const {return v[0];}
    [[nodiscard]] double y() const {return v[1];}
    [[nodiscard]] double z() const {return v[2];}

    Vec3 operator-() const {return Vec3(-v[0], -v[1], -v[2]);}
    double operator[](const int i) const {return v[i];}
    double& operator[](const int i) {return v[i];}

    Vec3& operator+=(const Vec3 &v2) {
        v[0] += v2.v[0];
        v[1] += v2.v[1];
        v[2] += v2.v[2];
        return *this;
    }

    Vec3& operator*=(const double t) {
        v[0] *= t;
        v[1] *= t;
        v[2] *= t;
        return *this;
    }

    Vec3& operator/=(const double t) {
        return *this *= 1/t;
    }

    [[nodiscard]] double length() const {
        return std::sqrt(squared_length());
    }

    [[nodiscard]] double squared_length() const {
        return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
    }

    [[nodiscard]] bool nearZero() const {
        double EPSILON = 1e-8;
        return std::fabs(v[0]) < EPSILON && std::fabs(v[1]) < EPSILON && std::fabs(v[2]) < EPSILON;
    }
    static Vec3 random() {
        return {randomDouble(), randomDouble(), randomDouble()};
    }

    static Vec3 random(double min, double max) {
        return {randomDouble(min, max), randomDouble(min, max), randomDouble(min, max)};
    }

};

using Point3 = Vec3;
using Color = Vec3;

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.v[0] << ' ' << v.v[1] << ' ' << v.v[2];
}

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
    return {v1.v[0] + v2.v[0], v1.v[1] + v2.v[1], v1.v[2] + v2.v[2]};
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
    return {v1.v[0] - v2.v[0], v1.v[1] - v2.v[1], v1.v[2] - v2.v[2]};
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return {v.v[0] * t, v.v[1] * t, v.v[2] * t};
}

inline Vec3 operator*(double t, const Vec3& v) {
    return {v.v[0] * t, v.v[1] * t, v.v[2] * t};
}

inline Vec3 operator*(const Vec3& v1, const Vec3& v2) {
    return {v1.v[0] * v2.v[0], v1.v[1] * v2.v[1], v1.v[2] * v2.v[2]};
}

inline Vec3 operator/(Vec3 v, double t) {
    return v * (1/t);
}

inline double dot(Vec3 v, Vec3 w) {
    return v.v[0] * w.v[0] + v.v[1] * w.v[1] + v.v[2] * w.v[2];
}

/*
 * 向量叉积
 */
inline Vec3 cross(const Vec3& v, const Vec3& w) {
    return {v.v[1] * w.v[2] - v.v[2] * w.v[1],
                v.v[2] * w.v[0] - v.v[0] * w.v[2],
                v.v[0] * w.v[1] - v.v[1] * w.v[0]};
}

inline Vec3 normalize(const Vec3& v) {
    return v / v.length();
}

const double EPSILON = 1e-60;

inline Vec3 randomUnitVector() {
    while (true) {
        auto p = Vec3::random(-1, 1);
        auto length_p = p.squared_length();
        if (length_p > EPSILON && length_p <= 1) {
            return p / std::sqrt(length_p);
        }
    }
}

inline Vec3 randomOnHemiSphere(const Vec3& normal) {
    Vec3 p = randomUnitVector();
    return dot(p, normal) > 0 ? p : -p;
}

inline Vec3 randomInUnitDisk() {
    while (true) {
        auto p = Vec3(randomDouble(-1, 1), randomDouble(-1, 1), 0);
        if (p.squared_length() < 1) {
            return p;
        }
    }
}

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2 * dot(v, n) * n;
}

inline Vec3 refract(const Vec3& in_dir, const Vec3& n, double etai_over_etat) {
    auto cos_theta = std::fmin(1.0, dot(-in_dir, n));
    //求解折射光线的垂直和水平分量
    Vec3 r_out_parallel = etai_over_etat * (in_dir + cos_theta * n);
    Vec3 r_out_perp = -std::sqrt(1.0 - r_out_parallel.squared_length()) * n;

    return r_out_parallel + r_out_perp;
}

#endif //VEC3_H
