#include <fstream>
#include <algorithm>

#include "../math/point.hpp"
#include "../core/ray_tracer.hpp"

#include "../core/object.hpp"
#include "../object/plane.hpp"
#include "../object/sphere.hpp"
#include "../object/triangle.hpp"

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
    Screen screen(1920, 1080, 90.0);

    Scene scene;
    scene.AddObject(make_shared<Sphere>(Point3d(-6.0, 5.0, -22.0), 5.0,
                                        make_shared<Diffuse>(kDiffuse, Vector3d(0.2, 1.0, 0.2))));
    scene.AddObject(make_shared<Sphere>(Point3d(6.0, 5.0, -22.0), 5.0,
                                        make_shared<Glossy>(kGlossy, Vector3d(0.2, 0.2, 1.0), 0.2, 500)));
    scene.AddObject(make_shared<Sphere>(Point3d(0.0, 5.0, -17.0), 2.5,
                                        make_shared<Glass>(kGlass, Vector3d(0.0), 1.3)));
    // scene.AddObject(make_shared<Plane>(Point3d(0.0), Vector3d(0.0, 1.0, 0.0),
    //                                     make_shared<Mirror>(kMirror, Vector3d(0.2, 0.2, 0.2), 0.8)));

    scene.AddLight(make_shared<DistantLight>(Vector3d(-1.0, -2.0, -1.0), 2.0));
    scene.AddLight(make_shared<DistantLight>(Vector3d(1.0, -2.0, -1.0), 2.0));

    auto objects = scene.objects();
    scene.BuildAABBTree(make_shared<AABBTree>(4, objects));

    RayTracer ray_tracer(screen, scene);
    ray_tracer.RayTracing();
    
    return 0;
}

