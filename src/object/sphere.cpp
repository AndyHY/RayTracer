#include "sphere.hpp"

bool Sphere::Hit(const Ray &ray, double t_min, double t_max, HitRecord &record) const {
    Vector3d   oc = ray.origin() - center_;
    double      a = Dot(ray.direction(), ray.direction());
    double half_b = Dot(oc, ray.direction());
    double      c = Dot(oc, oc) - radius_ * radius_;
    double  delta = half_b * half_b - a * c;
    if (delta < 0) {
        return false;
    } else {
        double t = (-half_b - sqrt(delta)) / a;
        if (t > t_min && t < t_max) {
            record.hit_t        = t;
            record.hit_point    = ray.At(t);
            record.hit_normal   = (ray.At(t) - center_) / radius_;
            record.hit_material = material_;
            return true;
        }
        t = (-half_b + sqrt(delta)) / a;
        if (t > t_min && t < t_max) {
            record.hit_t        = t;
            record.hit_point    = ray.At(t);
            record.hit_normal   = (ray.At(t) - center_) / radius_;
            record.hit_material = material_;
            return true;
        }
        return false;
    }
}