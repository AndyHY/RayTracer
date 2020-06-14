#include "ray_tracer.hpp"

#include <fstream>
#include <iostream>

#include "../math/point.hpp"
#include "../math/matrix.hpp"

void RayTracer::Render() {
    for (int x = 0; x < screen_.pixel_width; x += tile_size_)
        for (int y = 0; y < screen_.pixel_height; y += tile_size_)
            work_queue_.AddWork(WorkItem(x, y, tile_size_, tile_size_));
    
    for (int i = 0; i < num_threads_; i++)
        threads_[i] = std::thread(&RayTracer::ThreadTask, this);

    for (int i = 0; i < num_threads_; i++)
        threads_[i].join();
}

void RayTracer::ThreadTask() {
    WorkItem work_item;
    while (work_queue_.GetWork(work_item))
        RenderTile(work_item.tile_x, work_item.tile_y, work_item.tile_w, work_item.tile_h);

    num_done_++;
    if (num_done_ == num_threads_)
        SaveImage();
}

void RayTracer::RenderTile(int tile_x, int tile_y, int tile_w, int tile_h) {
    int begin_x = tile_x;
    int begin_y = tile_y;
    int end_x = std::min(begin_x + tile_w, screen_.pixel_width);
    int end_y = std::min(begin_y + tile_h, screen_.pixel_height);

    for (int x = begin_x; x < end_x; x++)
        for (int y = begin_y; y < end_y; y++)
            RenderPixel(x, y);
}

void RayTracer::RenderPixel(int a, int b) {
    double width = screen_.pixel_width;
    double height = screen_.pixel_height;

    double scale = tan(DegreeToRadian(screen_.vfov / 2));
    double aspect = static_cast<double>(width) / height;

    double x = (2 * ((a + 0.5) / width) - 1) * scale * aspect;
    double y = (1 - 2 * ((b + 0.5) / height)) * scale;

    Ray ray(Point3d(0.0), Vector3d(x, y, -1.0));

    Vector3d color;
    for (int i = 0; i < spp_; i++)
        color += Intersect(ray, scene_, 0);
    
    frame_buffer_[b * width + a] = Clamp(0.0, 1.0, color / spp_);
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
    if (!record.hit_material->IsDelta()) {
        for (const auto &light : lights) {
            Point3d light_pos; Vector3d light_normal; double light_pdf;
            auto Li = light->Sample(object_pos, light_pos, light_normal, light_pdf);

            auto wi = Normalize(light_pos - object_pos);

            Ray shadow_ray(object_pos, wi);
            HitRecord shadow_record;
            auto dis = (light_pos - object_pos).Length2();
            auto hit = scene.Hit(shadow_ray, kEpsilon, sqrt(dis), shadow_record);
            if (!hit) {
                auto f = record.hit_material->BSDF(wo, record, wi);
                auto cos_theta1 = std::abs(Dot(object_normal, wi));
                auto cos_theta2 = std::abs(Dot(light_normal, -wi));

                direct_light += Mult(Li, f) * cos_theta1 * cos_theta2 / dis / light_pdf;
            }
        }
    }

    Vector3d indirect_light(0.0);

    //计算间接光照
    if (RandomDouble() < RussianRoulette_) {
        Vector3d wi; double pdf;
        auto f = record.hit_material->Sample(wo, record, wi, pdf);

        Ray next_ray(object_pos, wi);
        auto Li = Intersect(next_ray, scene, depth + 1);
        
        auto cos_theta = std::abs(Dot(object_normal, wi));
        
        indirect_light += Mult(Li, f) * cos_theta / pdf / RussianRoulette_;
    }

    return direct_light + indirect_light;
}

void RayTracer::SaveImage() const {
    std::ofstream file("../image/image.ppm");
    file << "P3\n" << screen_.pixel_width << " " << screen_.pixel_height << "\n255\n";

    for (int i = 0; i < screen_.pixel_width * screen_.pixel_height; i++) {
        int r = static_cast<int>(255 * std::pow(frame_buffer_[i][0], 0.6));
        int g = static_cast<int>(255 * std::pow(frame_buffer_[i][1], 0.6));
        int b = static_cast<int>(255 * std::pow(frame_buffer_[i][2], 0.6));
        file << r << " " << g << " " << b << "\n";
    }
    
    file.close();
}