#include "Beckmann.hpp"

double BeckmannDistribution::RoughnessToAlpha(double roughness) {
    roughness = std::max(roughness, 1e-3);
    double x = std::log(roughness);
    return 1.62142 + 0.819955 * x + 0.1734 * x * x + 0.0171201 * x * x * x + 0.000640711 * x * x * x * x;
}

double BeckmannDistribution::D(const Vector3d &wh) const {
    double tan2_theta = Tan2Theta(wh);
    if (std::isinf(tan2_theta)) return 0.0;
    double cos4_theta = Cos2Theta(wh) * Cos2Theta(wh);
    double alpha2 = alpha_ * alpha_;
    return std::exp(-tan2_theta / alpha2) / (kPi * alpha2 * cos4_theta);
}

double BeckmannDistribution::Lambda(const Vector3d &w) const {
    double abs_tan_theta = std::abs(TanTheta(w));
    if (std::isinf(abs_tan_theta)) return 0.0;
    double a = 1 / (alpha_ * abs_tan_theta);
    if (a >= 1.6) return 0.0;
    return (1 - 1.259 * a + 0.396 * a * a) / (3.535 * a + 2.181 * a * a);
}

Vector3d BeckmannDistribution::SampleWh(const Vector3d &wo) const {
    double random1 = RandomDouble(), random2 = RandomDouble();
    double tan2_theta = -(alpha_ * alpha_) * std::log(1 - random1);
    double phi = 2 * kPi * random2;
    double cos_theta = 1 / std::sqrt(1 + tan2_theta);
    double sin_theta = std::sqrt(std::max(0.0, 1 - cos_theta * cos_theta));
    Vector3d wh = SphericalToCartesian(sin_theta, cos_theta, phi);
    if (!SameHemisphere(wh, wo)) wh = -wh;
    return wh;
}