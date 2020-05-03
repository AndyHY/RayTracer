#include "plane.hpp"

bool Plane::Hit(const Ray &ray, double t_min, double t_max, HitRecord &record) const {
    double denominator = Dot(ray.direction(), normal_);
    if (fabs(denominator) < kEpsilon)
        return false;
    
    double t = Dot(position_ - ray.origin(), normal_) / denominator;
    if (t < t_min || t > t_max)
        return false;
    
    record.hit_t        = t;
    record.hit_point    = ray.At(t);
    record.hit_normal   = normal_;
    record.hit_material = material_;
    
    return true;
}