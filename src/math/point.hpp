#ifndef POINT_HPP
#define POINT_HPP

#include <cassert>
#include "vector.hpp"

template <typename T>
class Point3 {
public:
    Point3() : x_(T{}), y_(T{}), z_(T{}) {}
    explicit Point3(T t)  : x_(t), y_(t), z_(t) {}
    Point3(T x, T y, T z) : x_(x), y_(y), z_(z) {}
    Point3(const Point3<T> &p) : x_(p.x_), y_(p.y_), z_(p.z_) {}
    Point3<T>& operator=(const Point3<T> &p) {
        x_ = p.x_;
        y_ = p.y_;
        z_ = p.z_;
        return *this;
    }

    Point3<T> operator+(const Vector3<T> &v) const {
        return Point3<T>(x_ + v.x_, y_ + v.y_, z_ + v.z_);
    }
    Vector3<T> operator-(const Point3<T> &p) const {
        return Vector3<T>(x_ - p.x_, y_ - p.y_, z_ - p.z_);
    }
    Point3<T>  operator*(T t) const {
        return Point3<T>(x_ * t, y_ * t, z_ * t);
    }
    Point3<T>  operator/(T t) const {
        return Point3<T>(x_ / t, y_ / t, z_ / t);
    }

    Point3<T>& operator*=(T t) {
        x_ *= t;
        y_ *= t;
        z_ *= t;
        return *this;
    }
    Point3<T>& operator/=(T t) {
        x_ /= t;
        y_ /= t;
        z_ /= t;
        return *this;
    }

    Point3<T> operator-() const { return Point3<T>(-x_, -y_, -z_); }

    T operator[](int i) const {
        assert(i >= 0 && i < 3);
        if (i == 0) return x_;
        if (i == 1) return y_;
        return z_;
    }

public:
    T x_, y_, z_;
};

typedef Point3<double> Point3d;
typedef Point3<float>  Point3f;
typedef Point3<int>    Point3i;

template<typename T>
inline Point3<T> operator*(T t, const Point3<T> &v) {
    return v * t;
}

#endif