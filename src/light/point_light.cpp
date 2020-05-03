#include "point_light.hpp"

void PointLight::Illuminate(const Point3d &hit_point, Vector3d &energy, Vector3d &dir, double &dis) const {
    dir = hit_point - pos_;
    double distance2 = dir.Length2();
    energy = color_ * intensity_ / (4 * kPi * distance2);
    dis = sqrt(distance2);
    dir.x_ /= dis; dir.y_ /= dis; dir.z_ /= dis;
}