#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "sampler.hpp"
#include "../math/utility.hpp"

enum Type { kDiffuse, kMirror, kGlossy, kGlass };

class Material {
public:
    Material(Type type, const Vector3d &albedo, const shared_ptr<Sampler3D> &sampler)
        : type_(type), albedo_(albedo), sampler_(sampler) {}
    virtual ~Material() = default;

    virtual void Sample(const Vector3d &wo, const Vector3d &n, Vector3d &wi, double &pdf) const = 0;
    
    virtual Vector3d BRDF(const Vector3d &wo, const Vector3d &n, const Vector3d &wi) const = 0;

    Type type() const { return type_; }
    const Vector3d& albedo() const { return albedo_; }

protected:
    Type     type_;
    Vector3d albedo_;
    shared_ptr<Sampler3D> sampler_;
};

#endif