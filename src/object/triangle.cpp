#include "triangle.hpp"

bool Triangle::Hit(const Ray &ray, double t_min, double t_max, HitRecord &record) const {
    Vector3d normal = Normalize(Cross(b_ - a_, c_ - a_));

    // double denominator = Dot(ray.direction(), normal);
    // if (fabs(denominator) < kEpsilon)
    //     return false;

    // double t = Dot(a_ - ray.origin(), normal) / denominator;
    // if (t < t_min || t > t_max)
    //     return false;

    // Vector3d p = ray.At(t);
    
    // Vector3d ab = b_ - a_;
    // Vector3d ap = p  - a_;
    // if (Dot(normal, Cross(ab, ap)) < 0)
    //     return false;

    // Vector3d bc = c_ - b_;
    // Vector3d bp = p  - b_;
    // if (Dot(normal, Cross(bc, bp)) < 0)
    //     return false;
    
    // Vector3d ca = a_ - c_;
    // Vector3d cp = p  - c_;
    // if (Dot(normal, Cross(ca, cp)) < 0)
    //     return false;
    
    // record.hit_t      = t;
    // record.hit_point  = p;
    // record.hit_normal = normal;
    // record.hit_object = this;

    // return true;

    Vector3d ba = a_ - b_;
    Vector3d ca = a_ - c_;
    Vector3d oa = a_ - ray.origin();

    double det = Dot(ba, Cross(ca, ray.direction()));
    if (fabs(det) < kEpsilon)
        return false;
    
    double u = Dot(oa, Cross(ca, ray.direction())) / det;
    if (u < 0 || u > 1)
        return false;
    
    double v = Dot(ba, Cross(oa, ray.direction())) / det;
    if (v < 0 || u + v > 1)
        return false;
    
    double t = Dot(ba, Cross(ca, oa)) / det;
    if (t < t_min || t > t_max)
        return false;
    
    record.hit_t        = t;
    record.hit_point    = ray.At(t);
    record.hit_normal   = normal;
    record.hit_material = material_;

    return true;
}