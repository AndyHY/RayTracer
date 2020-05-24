#ifndef RAY_HPP
#define RAY_HPP

#include "point.hpp"
#include "vector.hpp"

class Ray {
public:
    Ray(const Point3d &ori, const Vector3d &dir) : ori_(ori), dir_(Normalize(dir)) {}

    Point3d At(double t) const { return ori_ + t * dir_; }

    const Point3d&  origin()    const { return ori_; }
    const Vector3d& direction() const { return dir_; }

private:
    Point3d  ori_;  //origin
    Vector3d dir_;  //direction
};

#endif