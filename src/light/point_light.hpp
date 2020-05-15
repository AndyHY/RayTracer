#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "../core/light.hpp"

class PointLight : public Light {
public:
    PointLight(const Vector3d &radiance, const Point3d &pos)
        : Light(radiance), pos_(pos) {}
    
    virtual Vector3d Sample(const Point3d &object_pos, Point3d &light_pos, Vector3d &normal, double &pdf) const override;
    
    virtual bool Hit(const Ray &ray, double t_min, double t_max) const override;
    
private:
    Point3d pos_;  //position
};

#endif