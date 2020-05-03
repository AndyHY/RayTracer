#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "point.hpp"
#include "vector.hpp"
#include "utility.hpp"

template <typename T>
class Matrix44 {
public:
    Matrix44();
    Matrix44(T m00, T m01, T m02, T m03,
             T m10, T m11, T m12, T m13,
             T m20, T m21, T m22, T m23,
             T m30, T m31, T m32, T m33);
    Matrix44(const Matrix44<T> &rhs);
    Matrix44<T>& operator=(const Matrix44<T> &rhs);

    Matrix44<T> operator*(const Matrix44<T> &rhs) const;
    Vector3<T> operator*(const Vector3<T> &rhs) const;
    Point3<T> operator*(const Point3<T> &rhs) const;

    const T* operator[](int i) const { return m_[i]; }
    T* operator[](int i) { return m_[i]; }

public:
    T m_[4][4];
};

typedef Matrix44<double> Matrix44d;
typedef Matrix44<float>  Matrix44f;
typedef Matrix44<int>    Matrix44i;

template <typename T>
Matrix44<T>::Matrix44() {
    m_[0][0] = 1; m_[0][1] = 0; m_[0][2] = 0; m_[0][3] = 0;
    m_[1][0] = 0; m_[1][1] = 1; m_[1][2] = 0; m_[1][3] = 0;
    m_[2][0] = 0; m_[2][1] = 0; m_[2][2] = 1; m_[2][3] = 0;
    m_[3][0] = 0; m_[3][1] = 0; m_[3][2] = 0; m_[3][3] = 1;
}

template <typename T>
Matrix44<T>::Matrix44(T m00, T m01, T m02, T m03,
                      T m10, T m11, T m12, T m13,
                      T m20, T m21, T m22, T m23,
                      T m30, T m31, T m32, T m33) {
    m_[0][0] = m00; m_[0][1] = m01; m_[0][2] = m02; m_[0][3] = m03;
    m_[1][0] = m10; m_[1][1] = m11; m_[1][2] = m12; m_[1][3] = m13;
    m_[2][0] = m20; m_[2][1] = m21; m_[2][2] = m22; m_[2][3] = m23;
    m_[3][0] = m30; m_[3][1] = m31; m_[3][2] = m32; m_[3][3] = m33;
}

template <typename T>
Matrix44<T>::Matrix44(const Matrix44<T> &rhs) {
    for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
        m_[i][j] = rhs[i][j];
}

template <typename T>
Matrix44<T>& Matrix44<T>::operator=(const Matrix44<T> &rhs) {
    for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
        m_[i][j] = rhs[i][j];
    return *this;
}

template <typename T>
Matrix44<T> Matrix44<T>::operator*(const Matrix44<T> &rhs) const {
    Matrix44<T> matrix;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = m_[i][0] * rhs[0][j] + m_[i][1] * rhs[1][j]
                         + m_[i][2] * rhs[2][j] + m_[i][3] * rhs[3][j];
        }
    }
    return matrix;
}

template <typename T>
Vector3<T> Matrix44<T>::operator*(const Vector3<T> &rhs) const {
    T x = m_[0][0] * rhs[0] + m_[0][1] * rhs[1] + m_[0][2] * rhs[2] + m_[0][3] * 0;
    T y = m_[1][0] * rhs[0] + m_[1][1] * rhs[1] + m_[1][2] * rhs[2] + m_[1][3] * 0;
    T z = m_[2][0] * rhs[0] + m_[2][1] * rhs[1] + m_[2][2] * rhs[2] + m_[2][3] * 0;
    return Vector3<T>(x, y, z);
}

template <typename T>
Point3<T> Matrix44<T>::operator*(const Point3<T> &rhs) const {
    T x = m_[0][0] * rhs[0] + m_[0][1] * rhs[1] + m_[0][2] * rhs[2] + m_[0][3] * 1;
    T y = m_[1][0] * rhs[0] + m_[1][1] * rhs[1] + m_[1][2] * rhs[2] + m_[1][3] * 1;
    T z = m_[2][0] * rhs[0] + m_[2][1] * rhs[1] + m_[2][2] * rhs[2] + m_[2][3] * 1;
    T w = m_[3][0] * rhs[0] + m_[3][1] * rhs[1] + m_[3][2] * rhs[2] + m_[3][3] * 1;
    x /= w; y /= w; z /= w;
    return Point3<T>(x, y, z);
}

template <typename T>
Matrix44<T> Scale(T x, T y, T z) {
    return Matrix44<T>(
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    );
}

template <typename T>
Matrix44<T> Translate(T x, T y, T z) {
    return Matrix44<T>(
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    );
}

template <typename T>
Matrix44<T> RotateX(double angle) {
    double c = cos(DegreeToRadian(angle));
    double s = sin(DegreeToRadian(angle));
    return Matrix44<T>(
        1, 0,  0, 0,
        0, c, -s, 0,
        0, s,  c, 0,
        0, 0,  0, 1
    );
}

template <typename T>
Matrix44<T> RotateY(double angle) {
    double c = cos(DegreeToRadian(angle));
    double s = sin(DegreeToRadian(angle));
    return Matrix44<T>(
        c,  0, s, 0,
        0,  1, 0, 0,
        -s, 0, c, 0,
        0,  0, 0, 1
    );
}

template <typename T>
Matrix44<T> RotateZ(double angle) {
    double c = cos(DegreeToRadian(angle));
    double s = sin(DegreeToRadian(angle));
    return Matrix44<T>(
        c, -s, 0, 0,
        s,  c, 0, 0,
        0,  0, 1, 0,
        0,  0, 0, 1
    );
}

#endif