#include "glass.hpp"

void Glass::Sample(const Vector3d &wo, const Vector3d &n, Vector3d &wi, double &pdf) const {
    double kr = Fresnel(-wo, n, ior_);
    if (kr == 1.0) {    //total internal reflection
        wi = Reflect(-wo, n);
        pdf = 1.0;
    } else {
        double random_num = RandomDouble();
        if (random_num < kr) {
            wi = Reflect(-wo, n);
            pdf = kr;
        } else {
            wi = Refract(-wo, n, ior_);
            pdf = 1.0 - kr;
        }
    }
}

Vector3d Glass::BSDF(const Vector3d &wo, const Vector3d &n, const Vector3d &wi) const {
    double kr = Fresnel(-wo, n, ior_);
    double cos_theta = Dot(wo, n);
    if (kr == 1.0) {    //total internal reflection
        return reflectance_ / cos_theta;
    } else {
        double random_num = RandomDouble();
        if (random_num < kr)
            return kr * reflectance_ / cos_theta;
        else
            return (1.0 - kr) * refractance_ / cos_theta;   
    }
}