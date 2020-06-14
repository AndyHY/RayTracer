#ifndef MICROFACET_HPP
#define MICROFACET_HPP

#include "BSDF.hpp"

class MicrofacetDistribution {
public:
    MicrofacetDistribution() {}
    virtual ~MicrofacetDistribution() {}

    virtual double D(const Vector3d &wh) const = 0;
    virtual double Lambda(const Vector3d &w) const = 0;

    virtual Vector3d SampleWh(const Vector3d &wo) const = 0;

    double G1(const Vector3d &w) const;
    virtual double G(const Vector3d &wo, const Vector3d &wi) const;

    double PDF(const Vector3d &wo, const Vector3d &wh) const;
};

#endif