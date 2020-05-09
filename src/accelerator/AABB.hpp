#ifndef AABB_HPP
#define AABB_HPP

#include "../math/ray.hpp"
#include "../math/point.hpp"

class AABB {
public:
    AABB();
    AABB(const Point3d &pos1, const Point3d &pos2);

    bool Hit(const Ray &ray) const;
    int  MaxAxis() const;

    Vector3d Diagonal() const { return pos_max_ - pos_min_; }
    Point3d  Centroid() const { return (pos_min_ + pos_max_) / 2.0; }

    const Point3d& pos_min() const { return pos_min_; }
    const Point3d& pos_max() const { return pos_max_; }

private:
    Point3d pos_min_, pos_max_;
};

//合并两个AABB
inline AABB Union(const AABB &lhs, const AABB &rhs) {
    return AABB(
        Point3d::Min(lhs.pos_min(), rhs.pos_min()),
        Point3d::Max(lhs.pos_max(), rhs.pos_max())
    );
}

//合并两个AABB
inline AABB Union(const AABB &box, const Point3d &pos) {
    return AABB(
        Point3d::Min(box.pos_min(), pos),
        Point3d::Max(box.pos_max(), pos)
    );
}

#endif