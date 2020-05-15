#include "glossy.hpp"

void Glossy::Sample(const Vector3d &wo, const Vector3d &n, Vector3d &wi, double &pdf) const {

}

Vector3d Glossy::BRDF(const Vector3d &wo, const Vector3d &n, const Vector3d &wi) const {
    return Vector3d();
}