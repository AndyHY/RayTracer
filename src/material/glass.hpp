#ifndef GLASS_HPP
#define GLASS_HPP

#include "../core/material.hpp"

class Glass : public Material {
public:
    Glass(Type type, const Vector3d &albedo, double ior, const Vector3d &reflectance, const Vector3d &refractance)
        : Material(type, albedo), ior_(ior), reflectance_(reflectance), refractance_(refractance) {}

    virtual bool IsDelta() const override { return true; };

    virtual Vector3d Sample(const Vector3d &wo, const HitRecord &record, Vector3d &wi, double &pdf) const override;

    virtual Vector3d BSDF(const Vector3d &wo, const HitRecord &record, const Vector3d &wi) const override;

    double ior() const { return ior_; }

private:
    double ior_;            //index of refraction
    Vector3d reflectance_;    
    Vector3d refractance_;
};

#endif