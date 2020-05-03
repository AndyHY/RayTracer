#ifndef SCENE_HPP
#define SCENE_HPP

#include "light.hpp"
#include "object.hpp"

class Scene {
public:
    Scene() = default;
    Scene(const Scene &s) : objects_(s.objects_), lights_(s.lights_) {}

    void AddObject(const shared_ptr<Object> &object) { objects_.push_back(object); }
    void AddLight(const shared_ptr<Light> &light) { lights_.push_back(light); }

    bool Hit(const Ray &ray, double t_min, double t_max, HitRecord &hit_record) const;

    const vector<shared_ptr<Light>>& lights() const { return lights_; }

private:
    vector<shared_ptr<Object>> objects_;
    vector<shared_ptr<Light>>  lights_;
};

#endif