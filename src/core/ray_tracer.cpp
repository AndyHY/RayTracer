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
        for (int i = 0; i < screen_.pixel_width; i++) {
            double x = (2 * ((i + 0.5) / screen_.pixel_width) - 1) * scale * aspect;
            double y = (1 - 2 * ((j + 0.5) / screen_.pixel_height)) * scale;

            Ray ray(Point3d(0.0), Vector3d(x, y, -1.0));
            
            Vector3d color(0.0);
            for (int i = 0; i < ssp_; i++)
                color += Intersect(ray, scene_, 0);
            color = Clamp(0.0, 1.0, color / ssp_);

            int r = static_cast<int>(255 * std::pow(color[0], 0.6));
            int g = static_cast<int>(255 * std::pow(color[1], 0.6));
            int b = static_cast<int>(255 * std::pow(color[2], 0.6));
            file << r << " " << g << " " << b << "\n";
        }
        UpdateProgress(static_cast<double>(j) / screen_.pixel_height);
    }
    UpdateProgress(1.0);

    file.close();
}

Vector3d RayTracer::Intersect(const Ray &ray, const Scene &scene, int depth) const {
    auto lights = scene.lights();
    for (const auto &light : lights)
    if (light->Hit(ray, kEpsilon, kInfinity))
        return light->radiance();

    HitRecord record;
    if (!scene.Hit(ray, kEpsilon, kInfinity, record))
        return Vector3d(0.0);
    
    Vector3d direct_light(0.0);

    auto object_pos = record.hit_point;
    auto object_normal = record.hit_normal;
    auto wo = -ray.direction();

    //计算直接光照
    for (const auto &light : lights) {
        Point3d light_pos; Vector3d light_normal; double light_pdf;
        auto Li = light->Sample(object_pos, light_pos, light_normal, light_pdf);

        auto wi = Normalize(light_pos - object_pos);

        Ray shadow_ray(object_pos, wi);
        HitRecord shadow_record;
        auto dis = (light_pos - object_pos).Length2();
        auto hit = scene.Hit(shadow_ray, kEpsilon, sqrt(dis), shadow_record);
        if (!hit) {
            auto fr = record.hit_material->BRDF(wo, object_normal, wi);
            auto cos_theta1 = Dot(object_normal, wi);
            auto cos_theta2 = Dot(light_normal, -wi);
            direct_light += Mult(Li, fr) * cos_theta1 * cos_theta2 / dis / light_pdf;
        }
    }

    Vector3d indirect_light(0.0);

    //计算间接光照
    if (RandomDouble() < RussianRoulette_) {
        Vector3d wi; double pdf;
        record.hit_material->Sample(wo, object_normal, wi, pdf);

        Ray next_ray(object_pos, wi);
        auto Li = Intersect(next_ray, scene, depth + 1);
        auto fr = record.hit_material->BRDF(wo, object_normal, wi);
        auto cos_theta = Dot(object_normal, wi);
        
        indirect_light += Mult(Li, fr) * cos_theta / pdf / RussianRoulette_;
    }

    return direct_light + indirect_light;
}

void RayTracer::UpdateProgress(double progress) const
{
    int barWidth = 70;

    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << static_cast<int>(progress * 100.0) << " %\r";
    std::cout.flush();
};