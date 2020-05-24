#include "diffuse.hpp"
#include "../math/matrix.hpp"

Matrix44d LocalToWorld(const Vector3d &n) {
    Vector3d z = n;
    Vector3d h = z;
    if (fabs(h.x_) < fabs(h.y_) && fabs(h.x_) < fabs(h.z_))
        h.x_ = 1.0;
    else if (fabs(h.y_) < fabs(h.x_) && fabs(h.y_) < fabs(h.z_))
        h.y_ = 1.0;
    else
        h.z_ = 1.0;
    z = Normalize(z);
    Vector3d y = Cross(h, z);
    y = Normalize(y);
    Vector3d x = Cross(z, y);
    x = Normalize(x);
    return Matrix44d(
        x.x_, x.y_, x.z_, 0.0,
        y.x_, y.y_, y.z_, 0.0,
        z.x_, z.y_, z.z_, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

Vector3d LocalToWorld(const Vector3d &a, const Vector3d &N) {
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

void Diffuse::Sample(const Vector3d &wo, const Vector3d &n, Vector3d &wi, double &pdf) const {
    //wi = Normalize(LocalToWorld(n) * sampler_->Sample());
    double x1 = RandomDouble(), x2 = RandomDouble();    
    double z = fabs(1.0f - 2.0f * x1);                     
    double r = sqrt(1.0f - z * z), phi = 2 * M_PI * x2;    
    Vector3d local_ray(r * cos(phi), r * sin(phi), z);
    wi = Normalize(LocalToWorld(local_ray, n));
    pdf = 1 / (2 * kPi);
}

Vector3d Diffuse::BSDF(const Vector3d &wo, const Vector3d &n, const Vector3d &wi) const {
    return albedo_ / kPi;
}