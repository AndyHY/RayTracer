#ifndef RAY_TRACER_HPP
#define RAY_TRACER_HPP

#include "scene.hpp"

struct Screen {
    Screen(int w, int h, double fov) : pixel_width(w), pixel_height(h), vfov(fov) {}
    Screen(const Screen &s) : pixel_width(s.pixel_width), pixel_height(s.pixel_height), vfov(s.vfov) {}
        
    int pixel_width;
    int pixel_height;
    double vfov;
};

class RayTracer {
public:
    RayTracer(const Screen &screen, const Scene &scene, double RussianRoulette = 0.8, int spp = 8, int num_threads = 8)
        : screen_(screen), scene_(scene), RussianRoulette_(RussianRoulette), spp_(spp), num_threads_(num_threads) {}

    void RayTracing() const;

private:
    Vector3d Intersect(const Ray &ray, const Scene &scene, int depth) const;

    void UpdateProgress(double progress) const;

private:
    Screen screen_;
    Scene  scene_;
    double RussianRoulette_;
    int    spp_;
    int    num_threads_;
};

#endif