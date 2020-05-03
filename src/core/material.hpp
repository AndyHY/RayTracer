#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "../math/utility.hpp"

enum Type { kDiffuse, kMirror, kGlossy, kGlass };

class Material {
public:
    Material(Type type, const Vector3d &albedo) : type_(type), albedo_(albedo) {}
    virtual ~Material() = 0;

    Type type() const { return type_; }
    const Vector3d& albedo() const { return albedo_; }

protected:
    Type     type_;
    Vector3d albedo_;
};

#endif