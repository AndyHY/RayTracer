#ifndef DISTANT_LIGHT_HPP
#define DISTANT_LIGHT_HPP

#include "../core/light.hpp"

class DistantLight : public Light {
public:
    DistantLight(const Vector3d &radiance, const Vector3d &dir)
        : Light(radiance), dir_(Normalize(dir)) {}
    
    virtual Vector3d Sample(const Point3d &object_pos, Point3d &light_pos, Vector3d &normal, double &pdf) const override;

    virtual bool Hit(const Ray &ray, double t_min, double t_max) const override;

private:
    Vector3d dir_;  //direction
};

#endif