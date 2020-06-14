#include "glossy.hpp"

Vector3d Glossy::Sample(const Vector3d &wo, const HitRecord &record, Vector3d &wi, double &pdf) const {
    Vector3d local_wo = WorldToLocal(wo, record);
    Vector3d local_wh = distribution_->SampleWh(local_wo);
    if (Dot(local_wo, local_wh) < 0)
        return Vector3d(0.0);
    Vector3d local_wi = Reflect(local_wo, local_wh);
    if (!SameHemisphere(local_wo, local_wi))
        return Vector3d(0.0);
    wi  = LocalToWorld(local_wi, record);
    pdf = distribution_->PDF(local_wo, local_wh) / (4 * Dot(local_wo, local_wh));
    return BSDF(local_wo, record, local_wi);
}

Vector3d Glossy::BSDF(const Vector3d &wo, const HitRecord &record, const Vector3d &wi) const {
    Vector3d local_wo = WorldToLocal(wo, record);
    Vector3d local_wi = WorldToLocal(wi, record);
    double cos_theta_o = std::abs(CosTheta(local_wo)), cos_theta_i = std::abs(CosTheta(local_wi));
    Vector3d wh = local_wi + local_wo;
    if (cos_theta_i == 0 || cos_theta_o == 0) return Vector3d(0.0);
    if (wh.x_ == 0 && wh.y_ == 0 && wh.z_ == 0) return Vector3d(0.0);
    wh = Normalize(wh);
    return reflectance_ * distribution_->D(wh) * distribution_->G(local_wo, local_wi) / (4 * cos_theta_i * cos_theta_o);
}