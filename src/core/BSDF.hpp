#ifndef BSDF_HPP
#define BSDF_HPP

#include <algorithm>
#include "../math/vector.hpp"
#include "../math/utility.hpp"

inline double CosTheta (const Vector3d &w) { return w.z_; }
inline double Cos2Theta(const Vector3d &w) { return w.z_ * w.z_; }
inline double Sin2Theta(const Vector3d &w) { return std::max(0.0, 1.0 - Cos2Theta(w)); }
inline double SinTheta (const Vector3d &w) { return std::sqrt(Sin2Theta(w)); }
inline double TanTheta (const Vector3d &w) { return SinTheta(w) / CosTheta(w); }
inline double Tan2Theta(const Vector3d &w) { return Sin2Theta(w) / Cos2Theta(w); }

inline double CosPhi(const Vector3d &w) {
    double sin_theta = SinTheta(w);
    return (sin_theta == 0) ? 1.0 : Clamp(-1.0, 1.0, w.x_ / sin_theta);
}
inline double SinPhi(const Vector3d &w) {
    double sin_theta = SinTheta(w);
    return (sin_theta == 0) ? 0.0 : Clamp(-1.0, 1.0, w.y_ / sin_theta);
}
inline double Cos2Phi(const Vector3d &w) { return CosPhi(w) * CosPhi(w); }
inline double Sin2Phi(const Vector3d &w) { return SinPhi(w) * SinPhi(w); }

inline bool SameHemisphere(const Vector3d &w1, const Vector3d &w2) { return w1.z_ * w2.z_ > 0.0; }

#endif