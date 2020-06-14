#include "microfacet.hpp"

double MicrofacetDistribution::G1(const Vector3d &w) const {
    return 1 / (1 + Lambda(w));
}

double MicrofacetDistribution::G(const Vector3d &wo, const Vector3d &wi) const {
    return 1 / (1 + Lambda(wo) + Lambda(wi));
}

double MicrofacetDistribution::PDF(const Vector3d &wo, const Vector3d &wh) const {
    return D(wh) * G1(wo) * std::abs(Dot(wo, wh)) / std::abs(CosTheta(wo));
}