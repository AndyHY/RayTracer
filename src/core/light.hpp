#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "../math/point.hpp"
#include "../math/utility.hpp"

class Light {
public:
    Light(const Vector3d &radiance) : radiance_(radiance) {}
    virtual ~Light() = default;

    virtual Vector3d Sample(const Point3d &object_pos, Point3d &light_pos, Vector3d &normal, double &pdf) const = 0;

    virtual bool Hit(const Ray &ray, double t_min, double t_max) const = 0;

    const Vector3d& radiance() const { return radiance_; }

protected:
    Vector3d radiance_;
};

#endif