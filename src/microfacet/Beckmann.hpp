#ifndef BECKMANN_HPP
#define BECKMANN_HPP

#include "../core/microfacet.hpp"

class BeckmannDistribution : public MicrofacetDistribution {
public:
    BeckmannDistribution(double alpha) : alpha_(alpha) {}

    virtual double D(const Vector3d &wh) const override;
    virtual double Lambda(const Vector3d &w) const override;

    virtual Vector3d SampleWh(const Vector3d &wo) const override;

    static double RoughnessToAlpha(double roughness);

private:
    double alpha_;       // 只适用于各向同性表面
};

#endif