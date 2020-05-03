#ifndef SAMPLER_HPP
#define SAMPLER_HPP

#include "scene.hpp"

class Sampler {
public:
    static Vector3d Sample(const HitRecord &record, const Scene &scene, const Ray &ray, int depth);

    static Vector3d Intersect(const Ray &ray, const Scene &scene, int depth);

private:
    static Vector3d SampleDiffuse(const HitRecord &record, const Scene &scene);
    static Vector3d SampleMirror(const HitRecord &record, const Scene &scene, const Ray &ray, int depth);
    static Vector3d SampleGlossy(const HitRecord &record, const Scene &scene, const Ray &ray);
    static Vector3d SampleGlass(const HitRecord &record, const Scene &scene, const Ray &ray, int depth);
};

#endif