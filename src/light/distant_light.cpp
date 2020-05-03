#include "distant_light.hpp"

void DistantLight::Illuminate(const Point3d &hit_point, Vector3d &energy, Vector3d &dir, double &dis) const {
    energy = color_ * intensity_;
    dir = dir_;
    dis = kInfinity;
}