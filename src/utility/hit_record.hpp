#ifndef HIT_RECORD_HPP
#define HIT_RECORD_HPP

#include "../math/utility.hpp"

class Material;

struct HitRecord {
    double   hit_t;
    Point3d  hit_point;
    Vector3d hit_normal;
    shared_ptr<Material> hit_material;
    Vector3d ng, ns, ss, ts;
};

#endif