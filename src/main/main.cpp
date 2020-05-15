#include <chrono>
#include <iostream>
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
#include "../light/area_light.hpp"
#include "../light/point_light.hpp"
#include "../light/distant_light.hpp"

#include "../core/sampler.hpp"
#include "../sampler/uniform_sampler.hpp"

#include "../accelerator/AABB_tree.hpp"

int main(int argc, char **argv) {
    Screen screen(1080, 1080, 40.0);

    Scene scene;

    shared_ptr<Material> red = make_shared<Diffuse>(kDiffuse, Vector3d(0.63, 0.065, 0.05), make_shared<UniformHemiSampler3D>());
    shared_ptr<Material> green = make_shared<Diffuse>(kDiffuse, Vector3d(0.14, 0.45, 0.091), make_shared<UniformHemiSampler3D>());
    shared_ptr<Material> white = make_shared<Diffuse>(kDiffuse, Vector3d(0.725, 0.71, 0.68), make_shared<UniformHemiSampler3D>());

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
    
    Vector3d radiance = 8.0 * Vector3d(0.747+0.058, 0.747+0.258, 0.747) + 15.6 * Vector3d(0.740+0.287,0.740+0.160,0.740) + 18.4 * Vector3d(0.737+0.642,0.737+0.159,0.737);
    Point3d pos(0.0, 24.5, -100.0);
    Vector3d width(15.0, 0.0, 0.0);
    Vector3d height(0.0, 0.0, -15.0);
    Vector3d normal(0.0, -1.0, 0.0);
    AreaLight area_light(radiance, pos, width, height, normal, make_shared<UniformGridSampler2D>());
    scene.AddLight(make_shared<AreaLight>(area_light));

    auto objects = scene.objects();
    scene.BuildAABBTree(make_shared<AABBTree>(4, objects));

    RayTracer ray_tracer(screen, scene);

    auto start = std::chrono::system_clock::now();
    ray_tracer.RayTracing();
    auto stop  = std::chrono::system_clock::now();

    std::cout << "Render complete: \n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() << " minutes\n";
    std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << " seconds\n";

    return 0;
}

