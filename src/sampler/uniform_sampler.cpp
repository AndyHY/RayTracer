#include "uniform_sampler.hpp"
#include "../math/utility.hpp"

Vector2d UniformGridSampler2D::Sample() const {
    double x = RandomDouble();
    double y = RandomDouble();
    return Vector2d(x, y);
}

Vector3d UniformHemiSampler3D::Sample() const {
    double a = RandomDouble();
    double b = RandomDouble();

    double theta = acos(a);
    double phi = 2 * kPi * b;

    double x = sin(theta) * cos(phi);
    double y = sin(theta) * sin(phi);
    double z = cos(theta);

    return Vector3d(x, y, z);
}