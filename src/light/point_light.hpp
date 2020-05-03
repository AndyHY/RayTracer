#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "../core/light.hpp"

class PointLight : public Light {
public:
    PointLight(const Point3d &pos, double intensity = 1.0, const Vector3d &color = Vector3d(1.0))
        : Light(intensity, color), pos_(pos) {}
    
    virtual void Illuminate(const Point3d &hit_point, Vector3d &energy, Vector3d &dir, double &dis) const override;
    
private:
    Point3d pos_;  //position
};

#endif