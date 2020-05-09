#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "material.hpp"
#include "../math/point.hpp"
#include "../accelerator/AABB.hpp"
#include "../utility/hit_record.hpp"

class Object {
public:
    Object(const shared_ptr<Material> &material) : material_(material) {}
    virtual ~Object() = default;

    virtual bool Hit(const Ray &ray, double t_min, double t_max, HitRecord &record) const = 0;

    virtual AABB Box() const = 0;

protected:
    shared_ptr<Material> material_;
};

#endif