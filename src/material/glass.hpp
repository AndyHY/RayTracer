#ifndef GLASS_HPP
#define GLASS_HPP

#include "../core/material.hpp"

class Glass : public Material {
public:
    Glass(Type type, const Vector3d &albedo, const shared_ptr<Sampler3D> &sampler, double ior)
        : Material(type, albedo, sampler), ior_(ior) {}

    virtual void Sample(const Vector3d &wo, const Vector3d &n, Vector3d &wi, double &pdf) const override;

    virtual Vector3d BRDF(const Vector3d &wo, const Vector3d &n, const Vector3d &wi) const override;

    double ior() const { return ior_; }

private:
    double ior_;    //index of refraction
};

#endif