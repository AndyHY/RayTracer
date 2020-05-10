#include "triangle_mesh.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

TriangleMesh::TriangleMesh(const vector<int> &face_index, const vector<int> &vertex_index,
                           const vector<Point3d> &vertices, const shared_ptr<Material> &material) : Object(material) {
    num_tris_ = 0;
    for (auto face : face_index)
        num_tris_ += face - 2;
    
    vertex_index_ = vector<int>(3 * num_tris_);

    vertices_ = vertices;
    
    int t = 0;
    for (std::size_t i = 0, k = 0; i < face_index.size(); i++) {       //for each face
        for (int j = 0; j < face_index[i] - 2; j++) {                  //for each triangle
            vertex_index_[t]   = vertex_index[k];
            vertex_index_[t+1] = vertex_index[k+j+1];
            vertex_index_[t+2] = vertex_index[k+j+2];
            t += 3;
        }
        k += face_index[i];
    }

    for (auto &vertex : vertices_)
        box_ = Union(box_, vertex);
}

TriangleMesh TriangleMesh::CreateTriangleMesh(const string &file_path, const shared_ptr<Material> &material) {
    std::ifstream file(file_path);
    if (!file.is_open())
        std::cout << "object loading failed" << std::endl;
    
    std::stringstream ss;
    ss << file.rdbuf();

    int num_faces = 0;
    ss >> num_faces;

    vector<int> face_index(num_faces);
    int index_size = 0; 
    for (int i = 0; i < num_faces; i++) {
        ss >> face_index[i];
        index_size += face_index[i];
    }

    vector<int> vertex_index(index_size);
    int max_index = 0;
    for (int i = 0; i < index_size; i++) {
        ss >> vertex_index[i];
        if (max_index < vertex_index[i])
            max_index = vertex_index[i];
    }
    max_index++;

    vector<Point3d> vertices(max_index);
    for (int i = 0; i < max_index; i++) {
        ss >> vertices[i].x_ >> vertices[i].y_ >> vertices[i].z_;
    }

    file.close();

    return TriangleMesh(face_index, vertex_index, vertices, material);
}

bool TriangleHit(const Ray &ray, double t_min, double t_max, HitRecord &record,
                 const Point3d &a, const Point3d &b, const Point3d &c, const shared_ptr<Material> &material) {
    Vector3d normal = Normalize(Cross(b - a, c - a));
    Vector3d ba = a - b;
    Vector3d ca = a - c;
    Vector3d oa = a - ray.origin();

    double det = Dot(ba, Cross(ca, ray.direction()));
    if (fabs(det) < kEpsilon)
        return false;
    
    double u = Dot(oa, Cross(ca, ray.direction())) / det;
    if (u < 0 || u > 1)
        return false;
    
    double v = Dot(ba, Cross(oa, ray.direction())) / det;
    if (v < 0 || u + v > 1)
        return false;
    
    double t = Dot(ba, Cross(ca, oa)) / det;
    if (t < t_min || t > t_max)
        return false;
    
    record.hit_t        = t;
    record.hit_point    = ray.At(t);
    record.hit_normal   = normal;
    record.hit_material = material;

    return true;
}

bool TriangleMesh::Hit(const Ray &ray, double t_min, double t_max, HitRecord &hit_record) const {
    bool hit = false;
    HitRecord record;
    double max_t = t_max;
    int j = 0;
    for (int i = 0; i < num_tris_; i++) {
        const Point3d &a = vertices_[vertex_index_[j]];
        const Point3d &b = vertices_[vertex_index_[j+1]];
        const Point3d &c = vertices_[vertex_index_[j+2]];
        if (TriangleHit(ray, t_min, max_t, record, a, b, c, material_)) {
            max_t = record.hit_t;
            hit_record = record;
            hit = true;
        }
        j += 3;
    }
    return hit;
}