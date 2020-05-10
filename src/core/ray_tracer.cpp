#include "ray_tracer.hpp"
#include <iostream>
#include <fstream>
#include "../math/point.hpp"
#include "../math/matrix.hpp"

void RayTracer::RayTracing() const {
    std::ofstream file("../image/image.ppm");
    file << "P3\n" << screen_.pixel_width << " " << screen_.pixel_height << "\n255\n";

    double scale = tan(DegreeToRadian(screen_.vfov / 2));
    double aspect = static_cast<double>(screen_.pixel_width) / screen_.pixel_height;

    for (int j = 0; j < screen_.pixel_height; j++) {
        std::cout << "Scanlines remaining: " << screen_.pixel_height - j << std::endl;
        for (int i = 0; i < screen_.pixel_width; i++) {
            double x = (2 * ((i + 0.5) / screen_.pixel_width) - 1) * scale * aspect;
            double y = (1 - 2 * ((j + 0.5) / screen_.pixel_height)) * scale;

            //Matrix44d transform = Translate<double>(0.0, 5.0, 0.0);
            Point3d origin = Point3d(0.0);
            Vector3d direction = Vector3d(x, y, -1.0);

            Ray ray(origin, direction);
            Vector3d color = Sampler::Intersect(ray, scene_, 0);

            int r = static_cast<int>(255 * color[0]);
            int g = static_cast<int>(255 * color[1]);
            int b = static_cast<int>(255 * color[2]);
            file << r << " " << g << " " << b << "\n";
        }
    }
    
    std::cout << "Done." << std::endl;
    file.close();
}