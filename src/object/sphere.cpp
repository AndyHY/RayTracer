#include "sphere.hpp"

bool Sphere::Hit(const Ray &ray, double t_min, double t_max, HitRecord &record) const {
    Vector3d   oc = ray.origin() - center_;
    double      a = Dot(ray.direction(), ray.direction());
    double half_b = Dot(oc, ray.direction());
    double      c = Dot(oc, oc) - radius_ * radius_;
    double  delta = half_b * half_b - a * c;

    if (delta < 0.0) 
        return false;
    double t = (-half_b - sqrt(delta)) / a;
    if (t <= t_min || t >= t_max)
        t = (-half_b + sqrt(delta)) / a;
    if (t <= t_min || t >= t_max)
        return false;
    Point3d hit_point = ray.At(t);
    record.hit_t        = t;
    record.hit_point    = hit_point;
    record.hit_normal   = (hit_point - center_) / radius_;
    record.hit_material = material_;

    double phi = 0.0, theta = 0.0;
    double y = hit_point.y_ - center_.y_;
    double x = hit_point.x_ - center_.x_;
    double z = hit_point.z_ - center_.z_;
    if (x != 0.0)
        phi = std::atan2(y, x);
    if (phi < 0.0)
        phi += 2 * kPi;
    theta = std::acos(Clamp(-1.0, 1.0, z / radius_));
    double u = phi / (2 * kPi);
    double v = theta / kPi;

    double z_radius = std::sqrt(x * x + y * y);
    double cos_phi = x / z_radius;
    double sin_phi = y / z_radius;
    Vector3d dpdu(-2 * kPi * y, 2 * kPi * x, 0.0);
    Vector3d dpdv = kPi * Vector3d(z * cos_phi, z * sin_phi, -radius_ * std::sin(theta));

    record.ng = Normalize(Cross(dpdu, dpdv));
    record.ns = record.ng;
    record.ss = Normalize(dpdu);
    record.ts = Cross(record.ns, record.ss);
    
    return true;
}

AABB Sphere::Box() const {
    return AABB(center_ - radius_, center_ + radius_);
}