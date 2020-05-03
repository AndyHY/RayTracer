#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "../math/point.hpp"
#include "../math/utility.hpp"

class Light {
public:
    Light(double intensity, const Vector3d &color) : color_(color), intensity_(intensity) {}
    virtual ~Light() = default;

    virtual void Illuminate(const Point3d &hit_point, Vector3d &energy, Vector3d &dir, double &dis) const = 0;

protected:
    Vector3d color_;
    double intensity_;
};

#endif