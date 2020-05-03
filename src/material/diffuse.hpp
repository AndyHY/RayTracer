#ifndef DIFFUSE_HPP
#define DIFFUSE_HPP

#include "../core/material.hpp"

class Diffuse : public Material {
public:
    Diffuse(Type type, const Vector3d &albedo) : Material(type, albedo) {}

private:

};

#endif