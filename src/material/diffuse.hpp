#ifndef DIFFUSE_HPP
#define DIFFUSE_HPP

#include "../core/material.hpp"

class Diffuse : public Material {
public:
    Diffuse(Type type, const Vector3d &albedo, const shared_ptr<Sampler3D> &sampler)
        : Material(type, albedo, sampler) {}

    virtual void Sample(const Vector3d &wo, const Vector3d &n, Vector3d &wi, double &pdf) const override;

    virtual Vector3d BRDF(const Vector3d &wo, const Vector3d &n, const Vector3d &wi) const override;

private:

};

#endif