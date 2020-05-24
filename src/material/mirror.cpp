#include "mirror.hpp"

void Mirror::Sample(const Vector3d &wo, const Vector3d &n, Vector3d &wi, double &pdf) const {
    wi  = Reflect(-wo, n);
    pdf = 1.0;
}

Vector3d Mirror::BSDF(const Vector3d &wo, const Vector3d &n, const Vector3d &wi) const {
    double cos_theta = Dot(wo, n);
    return reflectance_ / cos_theta;
}