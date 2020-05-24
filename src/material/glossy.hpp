#ifndef GLOSSY_HPP
#define GLOSSY_HPP

#include "../core/material.hpp"

class Glossy : public Material {
public:
    Glossy(Type type, const Vector3d &albedo, const shared_ptr<Sampler3D> &sampler, double kd, double exp)
        : Material(type, albedo), sampler_(sampler), kd_(kd), ks_(1.0 - kd), exp_(exp) {}

    virtual bool IsDelta() const override { return false; };
    
    virtual void Sample(const Vector3d &wo, const Vector3d &n, Vector3d &wi, double &pdf) const override;

    virtual Vector3d BSDF(const Vector3d &wo, const Vector3d &n, const Vector3d &wi) const override;

    double kd()  const { return kd_; }
    double ks()  const { return ks_; }
    double exp() const { return exp_; }

private:
    shared_ptr<Sampler3D> sampler_;
    double kd_, ks_, exp_;    //k_diffuse, k_specular, exponent
};

#endif