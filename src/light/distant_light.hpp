#ifndef DISTANT_LIGHT_HPP
#define DISTANT_LIGHT_HPP

#include "../core/light.hpp"

class DistantLight : public Light {
public:
    DistantLight(const Vector3d &dir, double intensity = 1.0, const Vector3d &color = Vector3d(1.0))
        : Light(intensity, color), dir_(Normalize(dir)) {}
    
    virtual void Illuminate(const Point3d &hit_point, Vector3d &energy, Vector3d &dir, double &dis) const override;

private:
    Vector3d dir_;  //direction
};

#endif