#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "sampler.hpp"
#include "../math/utility.hpp"

enum Type { kDiffuse, kMirror, kGlossy, kGlass };

class Material {
public:
    Material(Type type, const Vector3d &albedo) : type_(type), albedo_(albedo) {}
    virtual ~Material() = default;

    virtual bool IsDelta() const = 0;

    virtual Vector3d Sample(const Vector3d &wo, const Vector3d &n, Vector3d &wi, double &pdf) const = 0;
    
    virtual Vector3d BSDF(const Vector3d &wo, const Vector3d &n, const Vector3d &wi) const = 0;

    Vector3d Reflect(const Vector3d &wo, const Vector3d &normal) const;
    bool Refract(const Vector3d &wo, const Vector3d &normal, double ior, Vector3d &wi) const;
    double   Fresnel(const Vector3d &wo, const Vector3d &normal, double ior) const;

    Type type() const { return type_; }
    const Vector3d& albedo() const { return albedo_; }

protected:
    Type     type_;
    Vector3d albedo_;
};

#endif