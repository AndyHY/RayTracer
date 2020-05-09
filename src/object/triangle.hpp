#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "../core/object.hpp"

class Triangle : public Object {
public:
    Triangle(const Point3d &a, const Point3d &b, const Point3d &c, const shared_ptr<Material> &material)
        : Object(material), a_(a), b_(b), c_(c) {}

    virtual bool Hit(const Ray &ray, double t_min, double t_max, HitRecord &record) const override;

    virtual AABB Box() const override;

private:
    Point3d a_, b_, c_;    //three vertices
};

#endif