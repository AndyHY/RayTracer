#include "distant_light.hpp"

Vector3d DistantLight::Sample(const Point3d &object_pos, Point3d &light_pos, Vector3d &normal, double &pdf) const {
    return Vector3d();
}

bool DistantLight::Hit(const Ray &ray, double t_min, double t_max) const {
    return false;
}