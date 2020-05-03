#ifndef RAY_TRACER_HPP
#define RAY_TRACER_HPP

#include "sampler.hpp"

struct Screen {
    Screen(int w, int h, double fov) : pixel_width(w), pixel_height(h), vfov(fov) {}
    Screen(const Screen &s) : pixel_width(s.pixel_width), pixel_height(s.pixel_height), vfov(s.vfov) {}
        
    int pixel_width;
    int pixel_height;
    double vfov;
};

class RayTracer {
public:
    RayTracer(const Screen &screen, const Scene &scene) : screen_(screen), scene_(scene) {}

    void RayTracing() const;

private:
    Screen screen_;
    Scene  scene_;
};

#endif