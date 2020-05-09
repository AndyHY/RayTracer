#ifndef SCENE_HPP
#define SCENE_HPP

#include "light.hpp"
#include "object.hpp"
#include "../accelerator/AABB_tree.hpp"

class Scene {
public:
    Scene() = default;
    Scene(const Scene &s) : objects_(s.objects_), lights_(s.lights_), tree_(s.tree_) {}

    void AddObject(const shared_ptr<Object> &object) { objects_.push_back(object); }
    void AddLight(const shared_ptr<Light> &light) { lights_.push_back(light); }
    void BuildAABBTree(const shared_ptr<AABBTree> &tree) { tree_ = tree; }

    bool Hit(const Ray &ray, double t_min, double t_max, HitRecord &hit_record) const;

    const vector<shared_ptr<Light>>&  lights()  const { return lights_; }
    const vector<shared_ptr<Object>>& objects() const { return objects_; }
    vector<shared_ptr<Object>> objects() { return objects_; }

private:
    bool HitAABBTree(const Ray &ray, const shared_ptr<AABBNode> &node,
                     double t_min, double t_max, HitRecord &hit_record) const;
    bool HitObjects(const Ray &ray, const vector<shared_ptr<Object>> &objects,
                    double t_min, double t_max, HitRecord &hit_record) const;

private:
    vector<shared_ptr<Object>> objects_;
    vector<shared_ptr<Light>>  lights_;
    shared_ptr<AABBTree> tree_;
};

#endif