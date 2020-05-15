#include "point_light.hpp"

Vector3d PointLight::Sample(const Point3d &object_pos, Point3d &light_pos, Vector3d &normal, double &pdf) const {
    return Vector3d();
}

bool PointLight::Hit(const Ray &ray, double t_min, double t_max) const {
    return false;
}