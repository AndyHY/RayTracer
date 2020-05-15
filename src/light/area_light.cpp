#include "area_light.hpp"

Vector3d AreaLight::Sample(const Point3d &object_pos, Point3d &light_pos, Vector3d &normal, double &pdf) const {
    Vector2d offset = sampler_->Sample() - Vector2d(0.5, 0.5);
    light_pos = pos_ + width_ * offset.x_ + height_ * offset.y_;
    normal = normal_;
    pdf = 1 / area_;
    return Dot(object_pos - light_pos, normal) > 0 ? radiance_ : Vector3d(0.0);
}

bool AreaLight::Hit(const Ray &ray, double t_min, double t_max) const {
    double denominator = Dot(ray.direction(), normal_);
    if (fabs(denominator) < kEpsilon)
        return false;
    
    double t = Dot(pos_ - ray.origin(), normal_) / denominator;
    if (t < t_min || t > t_max)
        return false;
    
    Point3d point = ray.origin() + t * ray.direction();
    Point3d a = pos_ + (-width_) / 2 + (-height_) / 2;
    Point3d b = pos_ + width_ / 2 + (-height_) / 2;
    Point3d c = pos_ + width_ / 2 + height_ / 2;
    Point3d d = pos_ + (-width_) / 2 + height_ / 2;

    Vector3d ap = point - a;
    Vector3d ab = b - a;

    Vector3d bp = point - b;
    Vector3d bc = c - b;

    Vector3d cp = point - c;
    Vector3d cd = d - c;

    Vector3d dp = point - d;
    Vector3d da = a - d;

    if (Dot(Cross(ap, ab), Cross(bp, bc)) < 0)
        return false;
    
    if (Dot(Cross(bp, bc), Cross(cp, cd)) < 0)
        return false;

    if (Dot(Cross(cp, cd), Cross(dp, da)) < 0)
        return false;

    return true;
}