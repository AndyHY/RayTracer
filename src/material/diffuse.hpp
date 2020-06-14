#ifndef DIFFUSE_HPP
#define DIFFUSE_HPP

#include "../core/material.hpp"

class Diffuse : public Material {
public:
    Diffuse(Type type, const Vector3d &albedo, const shared_ptr<Sampler3D> &sampler)
        : Material(type, albedo), sampler_(sampler) {}

    virtual bool IsDelta() const override { return false; };

    virtual Vector3d Sample(const Vector3d &wo, const HitRecord &record, Vector3d &wi, double &pdf) const override;

    virtual Vector3d BSDF(const Vector3d &wo, const HitRecord &record, const Vector3d &wi) const override;

    Vector3d LocalToWorld(const Vector3d &a, const Vector3d &N) const;

private:
    shared_ptr<Sampler3D> sampler_;
};

#endif