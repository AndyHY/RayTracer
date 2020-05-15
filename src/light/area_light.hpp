#ifndef AREA_LIGHT_HPP
#define AREA_LIGHT_HPP

#include "../core/light.hpp"
#include "../core/sampler.hpp"

class AreaLight : public Light {
public:
    AreaLight(const Vector3d &radiance, const Point3d &pos, const Vector3d &w,
              const Vector3d &h, const Vector3d &n, const shared_ptr<Sampler2D> &sampler) 
        : Light(radiance),
          pos_(pos),
          width_(w),
          height_(h),
          area_(w.Length() * h.Length()),
          normal_(Normalize(n)),
          sampler_(sampler) {}

    virtual Vector3d Sample(const Point3d &object_pos, Point3d &light_pos, Vector3d &normal, double &pdf) const override;

    virtual bool Hit(const Ray &ray, double t_min, double t_max) const override;

private:
    Point3d pos_;
    Vector3d width_, height_;
    double area_;
    Vector3d normal_;
    shared_ptr<Sampler2D> sampler_;
};

#endif