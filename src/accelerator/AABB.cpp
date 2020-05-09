#include "AABB.hpp"

#include <limits>
#include <iostream>
#include <algorithm>

AABB::AABB() {
    double min = std::numeric_limits<double>::lowest();
    double max = std::numeric_limits<double>::max();
    pos_min_ = Point3d(max, max, max);
    pos_max_ = Point3d(min, min, min);
}

AABB::AABB(const Point3d &pos1, const Point3d &pos2) {
    pos_min_ = Point3d(std::min(pos1.x_, pos2.x_), std::min(pos1.y_, pos2.y_), std::min(pos1.z_, pos2.z_));
    pos_max_ = Point3d(std::max(pos1.x_, pos2.x_), std::max(pos1.y_, pos2.y_), std::max(pos1.z_, pos2.z_));
}

//判断光线是否与AABB相交
bool AABB::Hit(const Ray &ray) const {
    double t_x_min = (pos_min_.x_ - ray.origin().x_) / ray.direction().x_;
    double t_x_max = (pos_max_.x_ - ray.origin().x_) / ray.direction().x_;
    if (t_x_min > t_x_max)
        std::swap(t_x_min, t_x_max);

    double t_y_min = (pos_min_.y_ - ray.origin().y_) / ray.direction().y_;
    double t_y_max = (pos_max_.y_ - ray.origin().y_) / ray.direction().y_;
    if (t_y_min > t_y_max)
        std::swap(t_y_min, t_y_max);

    double t_z_min = (pos_min_.z_ - ray.origin().z_) / ray.direction().z_;
    double t_z_max = (pos_max_.z_ - ray.origin().z_) / ray.direction().z_;
    if (t_z_min > t_z_max)
        std::swap(t_z_min, t_z_max);

    double t_min = std::max(t_x_min, std::max(t_y_min, t_z_min));
    double t_max = std::min(t_x_max, std::min(t_y_max, t_z_max));

    if (t_min < t_max && t_max > 0)
        return true;
    return false;
}

//确定最长的轴
int AABB::MaxAxis() const {
    Vector3d diag = Diagonal();
    if (diag.x_ > diag.y_ && diag.x_ > diag.z_)
        return 0;
    if (diag.y_ > diag.x_ && diag.y_ > diag.z_)
        return 1;
    return 2;
}