#include "mirror.hpp"

Vector3d Mirror::Sample(const Vector3d &wo, const HitRecord &record, Vector3d &wi, double &pdf) const {
    Vector3d n = record.hit_normal;
    wi  = Reflect(wo, n);
    pdf = 1.0;
    return reflectance_ / Dot(wi, n);
}

Vector3d Mirror::BSDF(const Vector3d &wo, const HitRecord &record, const Vector3d &wi) const {
    return Vector3d(0.0);
}