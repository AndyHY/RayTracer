#ifndef MIRROR_HPP
#define MiRROR_HPP

#include "../core/material.hpp"

class Mirror : public Material {
public:
    Mirror(Type type, const Vector3d &albedo, const shared_ptr<Sampler3D> &sampler, double km)
        : Material(type, albedo, sampler), km_(km) {}

    virtual void Sample(const Vector3d &wo, const Vector3d &n, Vector3d &wi, double &pdf) const override;

    virtual Vector3d BRDF(const Vector3d &wo, const Vector3d &n, const Vector3d &wi) const override;

    double km() const { return km_; }

private:
    double km_;  //k_mirror
};

#endif