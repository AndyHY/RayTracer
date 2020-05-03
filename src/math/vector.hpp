#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cassert>
#include <cmath>

template <typename T>
class Vector2 {
public:
    Vector2() : x_(T{}), y_(T{}) {}
    explicit Vector2(T t) : x_(t), y_(t) {}
    Vector2(T x, T y) : x_(x), y_(y) {}
    Vector2(const Vector2<T> &v) : x_(v.x_), y_(v.y_) {}
    Vector2<T>& operator=(const Vector2<T> &v) {
        x_ = v.x_;
        y_ = v.y_;
        return *this;
    }

    Vector2<T> operator+(const Vector2<T> &v) const {
        return Vector2<T>(x_ + v.x_, y_ + v.y_);
    }
    Vector2<T> operator-(const Vector2<T> &v) const {
        return Vector2<T>(x_ - v.x_, y_ - v.y_);
    }
    Vector2<T> operator*(T t) const {
        return Vector2<T>(x_ * t, y_ * t);
    }
    Vector2<T> operator/(T t) const {
        return Vector2<T>(x_ / t, y_ / t);
    }

    Vector2<T>& operator+=(const Vector2<T> &v) {
        x_ += v.x_;
        y_ += v.y_;
        return *this;
    }
    Vector2<T>& operator-=(const Vector2<T> &v) {
        x_ -= v.x_;
        y_ -= v.y_;
        return *this;
    }
    Vector2<T>& operator*=(T t) {
        x_ *= t;
        y_ *= t;
        return *this;
    }
    Vector2<T>& operator/=(T t) {
        x_ /= t;
        y_ /= t;
        return *this;
    }

    Vector2<T> operator-() const { return Vector2<T>(-x_, -y_); }

    T operator[](int i) const {
        assert(i >= 0 && i < 2);
        if (i == 0) return x_;
        return y_;
    }

    T Length2() const { return x_ * x_ + y_ * y_; }
    T Length () const { return sqrt(Length2()); }

public:
    T x_, y_;
};

typedef Vector2<double> Vector2d;
typedef Vector2<float>  Vector2f;
typedef Vector2<int>    Vector2i;

template<typename T>
inline Vector2<T> operator*(T t, const Vector2<T> &v) {
    return v * t;
}

template <typename T>
class Vector3 {
public:
    Vector3() : x_(T{}), y_(T{}), z_(T{}) {}
    explicit Vector3(T t)  : x_(t), y_(t), z_(t) {}
    Vector3(T x, T y, T z) : x_(x), y_(y), z_(z) {}
    Vector3(const Vector3<T> &v) : x_(v.x_), y_(v.y_), z_(v.z_) {}
    Vector3<T>& operator=(const Vector3<T> &v) {
        x_ = v.x_;
        y_ = v.y_;
        z_ = v.z_;
        return *this;
    }

    Vector3<T> operator+(const Vector3<T> &v) const {
        return Vector3<T>(x_ + v.x_, y_ + v.y_, z_ + v.z_);
    }
    Vector3<T> operator-(const Vector3<T> &v) const {
        return Vector3<T>(x_ - v.x_, y_ - v.y_, z_ - v.z_);
    }
    Vector3<T> operator*(T t) const {
        return Vector3<T>(x_ * t, y_ * t, z_ * t);
    }
    Vector3<T> operator/(T t) const {
        return Vector3<T>(x_ / t, y_ / t, z_ / t);
    }

    Vector3<T>& operator+=(const Vector3<T> &v) {
        x_ += v.x_;
        y_ += v.y_;
        z_ += v.z_;
        return *this;
    }
    Vector3<T>& operator-=(const Vector3<T> &v) {
        x_ -= v.x_;
        y_ -= v.y_;
        z_ -= v.z_;
        return *this;
    }
    Vector3<T>& operator*=(T t) {
        x_ *= t;
        y_ *= t;
        z_ *= t;
        return *this;
    }
    Vector3<T>& operator/=(T t) {
        x_ /= t;
        y_ /= t;
        z_ /= t;
        return *this;
    }

    Vector3<T> operator-() const { return Vector3<T>(-x_, -y_, -z_); }

    T operator[](int i) const {
        assert(i >= 0 && i < 3);
        if (i == 0) return x_;
        if (i == 1) return y_;
        return z_;
    }

    T Length2() const { return x_ * x_ + y_ * y_ + z_ * z_; }
    T Length () const { return sqrt(Length2()); }

public:
    T x_, y_, z_;
};

typedef Vector3<double> Vector3d;
typedef Vector3<float>  Vector3f;
typedef Vector3<int>    Vector3i;

template<typename T>
inline T Dot(const Vector3<T> &lhs, const Vector3<T> &rhs) {
    return lhs.x_ * rhs.x_ + lhs.y_ * rhs.y_ + lhs.z_ * rhs.z_;
}

template<typename T>
inline Vector3<T> Cross(const Vector3<T> &lhs, const Vector3<T> &rhs) {
    return Vector3<T>(
        lhs.y_ * rhs.z_ - lhs.z_ * rhs.y_,
        lhs.z_ * rhs.x_ - lhs.x_ * rhs.z_,
        lhs.x_ * rhs.y_ - lhs.y_ * rhs.x_
    );
}

template<typename T>
inline Vector3<T> Normalize(const Vector3<T> &v) {
    T len = v.Length();
    return v / len;
}

template<typename T>
inline Vector3<T> Mult(const Vector3<T> &lhs, const Vector3<T> &rhs) {
    return Vector3<T>(lhs.x_ * rhs.x_, lhs.y_ * rhs.y_, lhs.z_ * rhs.z_);
}

template<typename T>
inline Vector3<T> operator*(T t, const Vector3<T> &v) {
    return v * t;
}

#endif