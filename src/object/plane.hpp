#ifndef PLANE_HPP
#define PLANE_HPP

#include "../core/object.hpp"

class Plane : public Object {
public:
    Plane(const Point3d &position, const Vector3d &normal, const shared_ptr<Material> material)
        : Object(material), position_(position), normal_(Normalize(normal)) {}

    virtual bool Hit(const Ray &ray, double t_min, double t_max, HitRecord &record) const override;

private:
    Point3d  position_;
    Vector3d normal_;
};

#endif