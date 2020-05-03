#ifndef GLASS_HPP
#define GLASS_HPP

#include "../core/material.hpp"

class Glass : public Material {
public:
    Glass(Type type, const Vector3d &albedo, double ior)
        : Material(type, albedo), ior_(ior) {}

    double ior() const { return ior_; }

private:
    double ior_;    //index of refraction
};

#endif