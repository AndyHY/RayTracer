#include "ray.hpp"
#include <iostream>

Vector3d Ray::Reflect(const Vector3d &normal) const {
    return dir_ - 2 * Dot(dir_, normal) * normal;
}

Vector3d Ray::Refract(const Vector3d &normal, double ior) const {
    double eta1 = 1.0, eta2 = ior, eta;
    double cos1 = Dot(dir_, normal);
    Vector3d n = normal;

    if (cos1 < 0) {         //outside
        cos1 = -cos1;
        eta = eta1 / eta2; 
    } else {                //inside
        n = -n;
        eta = eta2 / eta1;
    }

    double cos22 = 1 - eta * eta * (1 - cos1 * cos1);

    if (cos22 < 0)  //total internal reflection
        return Vector3d(0.0);
    return eta * (dir_ + cos1 * n) - sqrt(cos22) * n;
}

double Ray::Fresnel(const Vector3d &normal, double ior) const {
    double eta1 = 1.0, eta2 = ior;
    double cos1 = Dot(dir_, normal);
    if (cos1 > 0) std::swap(eta1, eta2);
    cos1 = fabs(cos1);
    double eta  = eta1 / eta2;
    double cos22 = 1 - eta * eta * (1 - cos1 * cos1);
    if (cos22 < 0) return 1.0;  //total internal reflection
    double cos2 = sqrt(cos22);
    double r1 = (eta2 * cos1 - eta1 * cos2) / (eta2 * cos1 + eta1 * cos2);
    double r2 = (eta1 * cos1 - eta2 * cos2) / (eta1 * cos1 + eta2 * cos2);
    return (r1 * r1 + r2 * r2) / 2;
}