#ifndef AABB_TREE_HPP
#define AABB_TREE_HPP

#include <memory>

#include "AABB.hpp"
#include "../core/object.hpp"

struct AABBNode {
    AABB box;
    shared_ptr<AABBNode> left;
    shared_ptr<AABBNode> right;
    vector<shared_ptr<Object>> objects;
};

class AABBTree {
public:
    AABBTree(std::size_t capacity, vector<shared_ptr<Object>> &objects);

    const shared_ptr<AABBNode>& root() const { return root_; }

private:
    shared_ptr<AABBNode> BuildTree(vector<shared_ptr<Object>> &objects);

private:
    std::size_t capacity_;  //每个叶结点最多包含物体的个数
    shared_ptr<AABBNode> root_;
};

#endif