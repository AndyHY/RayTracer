#ifndef UNIFORM_SAMPLER_HPP
#define UNIFORM_SAMPLER_HPP

#include "../core/sampler.hpp"

//均匀格子采样
class UniformGridSampler2D : public Sampler2D {
public:
    virtual Vector2d Sample() const override;
};

//均匀半球采样
class UniformHemiSampler3D : public Sampler3D {
public:
    virtual Vector3d Sample() const override;
};

#endif