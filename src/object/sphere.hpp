#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "../core/object.hpp"

class Sphere : public Object {
public:
    Sphere(const Point3d &center, double radius, const shared_ptr<Material> &material)
        : Object(material), center_(center), radius_(radius) {}

    virtual bool Hit(const Ray &ray, double t_min, double t_max, HitRecord &record) const override;

    virtual AABB Box() const override;

private:
    Point3d center_;
    double  radius_;
};

#endif