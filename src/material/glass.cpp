#include "glass.hpp"

Vector3d Glass::Sample(const Vector3d &wo, const HitRecord &record, Vector3d &wi, double &pdf) const {
    Vector3d n = record.hit_normal;
    auto kr = Fresnel(-wo, n, ior_);
    auto rd = RandomDouble();
    //反射
    if (rd < kr) {
        wi  = Reflect(wo, n);
        pdf = kr;
        return reflectance_ * kr / std::abs(Dot(wi, n));
    }
    //折射
    if (!Refract(-wo, n, ior_, wi))
        return Vector3d(0.0);
    pdf = 1.0 - kr;
    auto cos_theta = Dot(wi, n);
    if (cos_theta < 0)   //入
        return refractance_  * (1 / ior_) * (1 / ior_) * (1.0 - kr) / std::abs(cos_theta);
    return refractance_  * ior_ * ior_ * (1.0 - kr) / std::abs(cos_theta);
}

Vector3d Glass::BSDF(const Vector3d &wo, const HitRecord &record, const Vector3d &wi) const {
    return Vector3d(0.0);
}