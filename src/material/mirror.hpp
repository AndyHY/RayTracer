#ifndef MIRROR_HPP
#define MiRROR_HPP

#include "../core/material.hpp"

class Mirror : public Material {
public:
    Mirror(Type type, const Vector3d &albedo, double km) : Material(type, albedo), km_(km) {}

    double km() const { return km_; }

private:
    double km_;  //k_mirror
};

#endif