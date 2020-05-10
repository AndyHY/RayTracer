#ifndef TRIANGLE_MESH_HPP
#define TRIANGLE_MESH_HPP

#include <vector>
#include "triangle.hpp"

using std::vector;
using std::string;

class TriangleMesh : public Object {
public:
    TriangleMesh(const vector<int> &face_index, const vector<int> &vertex_index,
                 const vector<Point3d> &vertices, const shared_ptr<Material> &material);
    static TriangleMesh CreateTriangleMesh(const string &file_path, const shared_ptr<Material> &material);

    virtual bool Hit(const Ray &ray, double t_min, double t_max, HitRecord &record) const override;

    virtual AABB Box() const override { return box_; }

private:
    int num_tris_;               //number of triangles
    vector<int> vertex_index_;   //index of vertices
    vector<Point3d> vertices_;   //coordinates of vertices
    AABB box_;                   //AABB
};

#endif