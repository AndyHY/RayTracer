#include "scene.hpp"

bool Scene::Hit(const Ray &ray, double t_min, double t_max, HitRecord &hit_record) const {
    return HitAABBTree(ray, tree_->root(), t_min, t_max, hit_record);
}

bool Scene::HitAABBTree(const Ray &ray, const shared_ptr<AABBNode> &node,
                        double t_min, double t_max, HitRecord &hit_record) const {
    if (!node->box.Hit(ray))
        return false;
    
    if (!node->left && !node->right)
        return HitObjects(ray, node->objects, t_min, t_max, hit_record);

    HitRecord record_left, record_right;
    bool left = false, right = false;
    if (node->left) 
        left = HitAABBTree(ray, node->left, t_min, t_max, record_left);
    if (node->right) 
        right = HitAABBTree(ray, node->right, t_min, t_max, record_right);
    
    if (left && right) {
        if (record_left.hit_t < record_right.hit_t)
            hit_record = record_left;
        else
            hit_record = record_right;
        return true;      
    }
    if (left) {
        hit_record = record_left;
        return true;
    }
    if (right) {
        hit_record = record_right;
        return true;
    }

    return false;
}

bool Scene::HitObjects(const Ray &ray, const vector<shared_ptr<Object>> &objects,
                       double t_min, double t_max, HitRecord &hit_record) const {
    bool hit = false;
    HitRecord record;
    double max_t = t_max;
    for (const auto &object : objects) {
        if (object->Hit(ray, t_min, max_t, record)) {
            max_t = record.hit_t;
            hit_record = record;
            hit = true;
        }
    }
    return hit;
}

