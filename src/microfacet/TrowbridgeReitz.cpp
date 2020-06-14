#include "TrowbridgeReitz.hpp"

double TrowbridgeReitzDistribution::RoughnessToAlpha(double roughness) {
    roughness = std::max(roughness, 1e-3);
    double x = std::log(roughness);
    return 1.62142 + 0.819955 * x + 0.1734 * x * x + 0.0171201 * x * x * x + 0.000640711 * x * x * x * x;
}

double TrowbridgeReitzDistribution::D(const Vector3d &wh) const {
    double tan2_theta = Tan2Theta(wh);
    if (std::isinf(tan2_theta)) return 0.0;
    double cos4_theta = Cos2Theta(wh) * Cos2Theta(wh);
    double alpha2 = alpha_ * alpha_;
    double e = tan2_theta / alpha2;
    return 1 / (kPi * alpha2 * cos4_theta * (1 + e) * (1 + e));
}

double TrowbridgeReitzDistribution::Lambda(const Vector3d &w) const {
    double tan2_theta = Tan2Theta(w);
    if (std::isinf(tan2_theta)) return 0.0;
    return (-1 + std::sqrt(1 + alpha_ * alpha_ * tan2_theta)) / 2.0;
}

Vector3d TrowbridgeReitzDistribution::SampleWh(const Vector3d &wo) const {
    double random1 = RandomDouble(), random2 = RandomDouble();
    double tan2_theta = alpha_ * alpha_ * random1 / (1.0 - random1);
    double phi = 2 * kPi * random2;
    double cos_theta = 1 / std::sqrt(1 + tan2_theta);
    double sin_theta = std::sqrt(std::max(0.0, 1 - cos_theta * cos_theta));
    Vector3d wh = SphericalToCartesian(sin_theta, cos_theta, phi);
    if (!SameHemisphere(wh, wo)) wh = -wh;
    return wh;
}