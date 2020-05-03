#ifndef GLOSSY_HPP
#define GLOSSY_HPP

#include "../core/material.hpp"

class Glossy : public Material {
public:
    Glossy(Type type, const Vector3d &albedo, double kd, double exp)
        : Material(type, albedo), kd_(kd), ks_(1.0 - kd), exp_(exp) {}

    double kd()  const { return kd_; }
    double ks()  const { return ks_; }
    double exp() const { return exp_; }

private:
    double kd_, ks_, exp_;    //k_diffuse, k_specular, exponent
};

#endif