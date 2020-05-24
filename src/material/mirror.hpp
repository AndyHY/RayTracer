#ifndef MIRROR_HPP
#define MiRROR_HPP

#include "../core/material.hpp"

class Mirror : public Material {
public:
    Mirror(Type type, const Vector3d &albedo, const Vector3d &reflectance)
        : Material(type, albedo), reflectance_(reflectance) {}

    virtual bool IsDelta() const override { return true; };

    virtual void Sample(const Vector3d &wo, const Vector3d &n, Vector3d &wi, double &pdf) const override;

    virtual Vector3d BSDF(const Vector3d &wo, const Vector3d &n, const Vector3d &wi) const override;

private:
    Vector3d reflectance_;
};

#endif