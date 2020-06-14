#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <vector>
#include <memory> 
#include <limits>
#include <random>
#include <algorithm>

#include "ray.hpp"

using std::vector;
using std::shared_ptr;
using std::make_shared;

const double kPi = 3.141592653589793238;
const double kInfinity = std::numeric_limits<double>::max();
const double kEpsilon = 1e-4;

inline double DegreeToRadian(double degree) {
    return degree * (kPi / 180.0);
}

inline double RadianToDegree(double radian) {
    return radian * (180.0 / kPi);
}

inline Vector3d SphericalToCartesian(double sin_theta, double cos_theta, double phi) {
    return Vector3d(sin_theta * std::cos(phi), sin_theta * std::sin(phi), cos_theta);
}

inline double Clamp(double low, double high, double value) {
    return std::max(low, std::min(high, value));
}

inline Vector3d Clamp(double low, double high, const Vector3d &v) {
    return Vector3d(
        Clamp(low, high, v.x_),
        Clamp(low, high, v.y_),
        Clamp(low, high, v.z_)
    );
}

inline double RandomDouble() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(rng);
}

#endif