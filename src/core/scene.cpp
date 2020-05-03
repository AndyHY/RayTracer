#include "scene.hpp"

bool Scene::Hit(const Ray &ray, double t_min, double t_max, HitRecord &hit_record) const {
    bool hit = false;
    HitRecord record;
    double max_t = t_max;
    for (const auto &object : objects_) {
        if (object->Hit(ray, t_min, max_t, record)) {
            max_t = record.hit_t;
            hit_record = record;
            hit = true;
        }
    }
    return hit;
}