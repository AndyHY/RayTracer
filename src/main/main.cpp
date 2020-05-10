#include <fstream>
#include <algorithm>

#include "../math/point.hpp"
#include "../core/ray_tracer.hpp"

#include "../core/object.hpp"
#include "../object/plane.hpp"
#include "../object/sphere.hpp"
#include "../object/triangle.hpp"
#include "../object/triangle_mesh.hpp"

#include "../core/material.hpp"
#include "../material/glass.hpp"
#include "../material/mirror.hpp"
#include "../material/glossy.hpp"
#include "../material/diffuse.hpp"

#include "../core/light.hpp"
#include "../light/point_light.hpp"
#include "../light/distant_light.hpp"

#include "../accelerator/AABB_tree.hpp"

int main(int argc, char **argv) {
    Screen screen(1080, 1080, 40.0);

    Scene scene;

    shared_ptr<Material> red = make_shared<Diffuse>(kDiffuse, Vector3d(0.63, 0.065, 0.05));
    shared_ptr<Material> green = make_shared<Diffuse>(kDiffuse, Vector3d(0.14, 0.45, 0.091));
    shared_ptr<Material> white = make_shared<Diffuse>(kDiffuse, Vector3d(0.725, 0.71, 0.68));

    TriangleMesh left_wall = TriangleMesh::CreateTriangleMesh("../models/Cornellbox/left.obj", red);
    scene.AddObject(make_shared<TriangleMesh>(left_wall));

    TriangleMesh right_wall = TriangleMesh::CreateTriangleMesh("../models/Cornellbox/right.obj", green);
    scene.AddObject(make_shared<TriangleMesh>(right_wall));

    TriangleMesh back_wall = TriangleMesh::CreateTriangleMesh("../models/Cornellbox/back.obj", white);
    scene.AddObject(make_shared<TriangleMesh>(back_wall));

    TriangleMesh floor = TriangleMesh::CreateTriangleMesh("../models/Cornellbox/floor.obj", white);
    scene.AddObject(make_shared<TriangleMesh>(floor));

    TriangleMesh ceiling = TriangleMesh::CreateTriangleMesh("../models/Cornellbox/ceiling.obj", white);
    scene.AddObject(make_shared<TriangleMesh>(ceiling));

    TriangleMesh tall_cube = TriangleMesh::CreateTriangleMesh("../models/Cornellbox/tall_cube.obj", white);
    scene.AddObject(make_shared<TriangleMesh>(tall_cube));

    TriangleMesh short_cube = TriangleMesh::CreateTriangleMesh("../models/Cornellbox/short_cube.obj", white);
    scene.AddObject(make_shared<TriangleMesh>(short_cube));
    
    scene.AddLight(make_shared<PointLight>(Point3d(0.0, 24.5, -100.0), 50000.0));

    auto objects = scene.objects();
    scene.BuildAABBTree(make_shared<AABBTree>(4, objects));

    RayTracer ray_tracer(screen, scene);
    ray_tracer.RayTracing();
    
    return 0;
}

