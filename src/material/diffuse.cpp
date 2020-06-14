#include "diffuse.hpp"

Vector3d Diffuse::LocalToWorld(const Vector3d &a, const Vector3d &N) const {
    Vector3d B, C;
    if (fabs(N.x_) > fabs(N.y_)) {
        double inv_len = 1.0 / sqrt(N.x_ * N.x_ + N.z_ * N.z_);
        C = Vector3d(N.z_ * inv_len, 0.0f, -N.x_ * inv_len);
    } else {
        double inv_len = 1.0 / sqrt(N.y_ * N.y_ + N.z_ * N.z_);
        C = Vector3d(0.0f, N.z_ * inv_len, -N.y_ * inv_len);
    }
    B = Cross(C, N);
    return a.x_ * B + a.y_ * C + a.z_ * N;
}

Vector3d Diffuse::Sample(const Vector3d &wo, const HitRecord &record, Vector3d &wi, double &pdf) const {
    //wi = Normalize(LocalToWorld(n) * sampler_->Sample());
    double x1 = RandomDouble(), x2 = RandomDouble();    
    double z = fabs(1.0f - 2.0f * x1);                     
    double r = sqrt(1.0f - z * z), phi = 2 * M_PI * x2;    
    Vector3d local_ray(r * cos(phi), r * sin(phi), z);
    wi  = Normalize(LocalToWorld(local_ray, record.hit_normal));
    pdf = 1 / (2 * kPi);
    return albedo_ / kPi;
}

Vector3d Diffuse::BSDF(const Vector3d &wo, const HitRecord &record, const Vector3d &wi) const {
    return albedo_ / kPi;
}