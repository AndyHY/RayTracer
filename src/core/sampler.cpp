#include "sampler.hpp"
// #include "../material/glass.hpp"
// #include "../material/mirror.hpp"
// #include "../material/glossy.hpp"

// Vector3d Sampler::Sample(const HitRecord &record, const Scene &scene, const Ray &ray, int depth) {
//     switch (record.hit_material->type()) {
//         case kDiffuse: 
//             return SampleDiffuse(record, scene);
//         case kMirror:
//             return SampleMirror(record, scene, ray, depth);
//         case kGlossy:
//             return SampleGlossy(record, scene, ray);
//         case kGlass:
//             return SampleGlass(record, scene, ray, depth);
//     }
//     return Vector3d(0.0);
// }

// Vector3d Sampler::SampleDiffuse(const HitRecord &record, const Scene &scene) {
//     Vector3d color(0.2);    //ambient color

//     auto lights = scene.lights();
//     for (const auto &light : lights) {
//         Vector3d light_energy, light_direct;
//         double distance;
//         light->Illuminate(record.hit_point, light_energy, light_direct, distance);

//         Ray shadow_ray(record.hit_point, -light_direct);
//         HitRecord shadow_record;

//         if (!scene.Hit(shadow_ray, kEpsilon, distance, shadow_record)) {
//             color += Mult(record.hit_material->albedo() / kPi * std::max(0.0, Dot(record.hit_normal, -light_direct)), light_energy);
//         }
//     }

//     return Clamp(0.0, 1.0, color);
// }

// Vector3d Sampler::SampleMirror(const HitRecord &record, const Scene &scene, const Ray &ray, int depth) {
//     Vector3d color(0.2);
//     Mirror *mirror = static_cast<Mirror*>(record.hit_material.get());

//     auto lights = scene.lights();
//     for (const auto &light : lights) {
//         Vector3d light_energy, light_direct;
//         double distance;
//         light->Illuminate(record.hit_point, light_energy, light_direct, distance);

//         Ray shadow_ray(record.hit_point, -light_direct);
//         HitRecord shadow_record;

//         if (!scene.Hit(shadow_ray, kEpsilon, distance, shadow_record)) {
//             Ray reflected_ray = Ray(record.hit_point, ray.Reflect(record.hit_normal));
//             color += mirror->km() * Intersect(reflected_ray, scene, depth + 1);
//         }
//     }

//     return Clamp(0.0, 1.0, color);
// }

// Vector3d Sampler::SampleGlossy(const HitRecord &record, const Scene &scene, const Ray &ray) {
//     Vector3d color(0.2);    //ambient color
//     Vector3d diffuse_color(0.0), specular_color(0.0);
//     Glossy *glossy = static_cast<Glossy*>(record.hit_material.get());

//     auto lights = scene.lights();
//     for (const auto &light : lights) {
//         Vector3d light_energy, light_direct;
//         double distance;
//         light->Illuminate(record.hit_point, light_energy, light_direct, distance);

//         Ray shadow_ray(record.hit_point, -light_direct);
//         HitRecord shadow_record;

//         if (!scene.Hit(shadow_ray, kEpsilon, distance, shadow_record)) {
//             diffuse_color = Mult(glossy->albedo() * std::max(0.0, Dot(record.hit_normal, -light_direct)), light_energy);

//             Vector3d h = Normalize(-ray.direction() - light_direct);
//             specular_color = light_energy * std::pow(std::max(0.0, Dot(h, record.hit_normal)), glossy->exp()); 
//         }
//     }

//     color += glossy->kd() * diffuse_color + glossy->ks() * specular_color;
//     return Clamp(0.0, 1.0, color);
// }

// Vector3d Sampler::SampleGlass(const HitRecord &record, const Scene &scene, const Ray &ray, int depth) {
//     Vector3d color(0.0);    
//     Vector3d reflect_color(0.0), refract_color(0.0);
//     Glass *glass = static_cast<Glass*>(record.hit_material.get());

//     double kr = ray.Fresnel(record.hit_normal, glass->ior());

//     if (kr < 1.0) {
//         Ray refract_ray(record.hit_point, ray.Refract(record.hit_normal, glass->ior()));
//         refract_color = Intersect(refract_ray, scene, depth + 1);
//     }

//     Ray reflect_ray(record.hit_point, ray.Reflect(record.hit_normal));
//     reflect_color = Intersect(reflect_ray, scene, depth + 1);

//     color += kr * reflect_color + (1.0 - kr) * refract_color;
//     return Clamp(0.0, 1.0, color);
// }