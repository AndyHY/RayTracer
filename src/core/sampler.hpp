#ifndef SAMPLER_HPP
#define SAMPLER_HPP

#include "../math/vector.hpp"

// class Sampler {
// public:
//     static Vector3d Sample(const HitRecord &record, const Scene &scene, const Ray &ray, int depth);

// private:
//     static Vector3d SampleDiffuse(const HitRecord &record, const Scene &scene);
//     static Vector3d SampleMirror(const HitRecord &record, const Scene &scene, const Ray &ray, int depth);
//     static Vector3d SampleGlossy(const HitRecord &record, const Scene &scene, const Ray &ray);
//     static Vector3d SampleGlass(const HitRecord &record, const Scene &scene, const Ray &ray, int depth);
// };

class Sampler3D {
public:
    virtual ~Sampler3D() = default;

    virtual Vector3d Sample() const = 0;
};

class Sampler2D {
public:
    virtual ~Sampler2D() = default;

    virtual Vector2d Sample() const = 0;
};

#endif