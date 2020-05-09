#include "AABB_tree.hpp"

AABBTree::AABBTree(std::size_t capacity, vector<shared_ptr<Object>> &objects)
    : capacity_(capacity), root_(BuildTree(objects)) {}

shared_ptr<AABBNode> AABBTree::BuildTree(vector<shared_ptr<Object>> &objects) {
    shared_ptr<AABBNode> node = make_shared<AABBNode>();

    if (objects.size() <= capacity_) {
        for (const auto &object : objects) {
            node->box = Union(node->box, object->Box());
            node->objects.push_back(object);
        }
        node->left  = nullptr;
        node->right = nullptr;
    } else {
        AABB box;
        for (const auto &object : objects) {
            box = Union(box, object->Box());
        }

        int det = box.MaxAxis();
        switch (det) {
            case 0:
                std::sort(objects.begin(), objects.end(), [](auto it1, auto it2) {
                    return it1->Box().Centroid().x_ < it2->Box().Centroid().x_;
                });
                break;
            case 1:
                std::sort(objects.begin(), objects.end(), [](auto it1, auto it2) {
                    return it1->Box().Centroid().y_ < it2->Box().Centroid().y_;
                });
                break;
            case 2:
                std::sort(objects.begin(), objects.end(), [](auto it1, auto it2) {
                    return it1->Box().Centroid().z_ < it2->Box().Centroid().z_;
                });
                break;
        }

        auto begin = objects.begin();
        auto mid = begin + objects.size() / 2;
        auto end = objects.end();

        auto left_objects  = vector<shared_ptr<Object>>(begin, mid);
        auto right_objects = vector<shared_ptr<Object>>(mid, end);

        node->left  = BuildTree(left_objects);
        node->right = BuildTree(right_objects);
        node->box = Union(node->left->box, node->right->box);
    }

    return node;
}