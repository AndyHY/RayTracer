#ifndef GLOSSY_HPP
#define GLOSSY_HPP

#include "../core/material.hpp"
#include "../core/microfacet.hpp"

class Glossy : public Material {
public:
    Glossy(Type type, const Vector3d &albedo, const Vector3d &reflectance,
           const shared_ptr<MicrofacetDistribution> &distribution)
        : Material(type, albedo), reflectance_(reflectance), distribution_(distribution) {}

    virtual bool IsDelta() const override { return false; };
    
    virtual Vector3d Sample(const Vector3d &wo,const HitRecord &record, Vector3d &wi, double &pdf) const override;

    virtual Vector3d BSDF(const Vector3d &wo,const HitRecord &record, const Vector3d &wi) const override;

private:
    Vector3d reflectance_;
    shared_ptr<MicrofacetDistribution> distribution_;
};

#endif