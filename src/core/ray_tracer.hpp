#ifndef RAY_TRACER_HPP
#define RAY_TRACER_HPP

#include <atomic>
#include <thread>
#include "scene.hpp"
#include "../utility/work_queue.hpp"

struct Screen {
    Screen(int w, int h, double fov) : pixel_width(w), pixel_height(h), vfov(fov) {}
    Screen(const Screen &s) : pixel_width(s.pixel_width), pixel_height(s.pixel_height), vfov(s.vfov) {}
        
    int pixel_width;
    int pixel_height;
    double vfov;
};

struct WorkItem {
    WorkItem() : WorkItem(0, 0, 0, 0) {}
    WorkItem(int x, int y, int w, int h) : tile_x(x), tile_y(y), tile_w(w), tile_h(h) {}

    int tile_x, tile_y;
    int tile_w, tile_h;
};

class RayTracer {
public:
    RayTracer(const Screen &screen, const Scene &scene, double RussianRoulette = 0.8,
              int spp = 32, int num_threads = 8, int num_done = 0, int tile_size = 32)
        : screen_(screen),
          scene_(scene), 
          RussianRoulette_(RussianRoulette),
          spp_(spp),
          num_threads_(num_threads),
          tile_size_(tile_size),
          num_done_(num_done) { 
        threads_.resize(num_threads_);
        frame_buffer_.resize(screen_.pixel_width * screen_.pixel_height);
    }

    void Render();

private:
    void ThreadTask();
    void RenderTile(int tile_x, int tile_y, int tile_w, int tile_h);
    void RenderPixel(int x, int y);

    Vector3d Intersect(const Ray &ray, const Scene &scene, int depth) const;

    void SaveImage() const;

private:
    Screen screen_;
    Scene  scene_;
    double RussianRoulette_;
    int    spp_;
    int    num_threads_;
    int    tile_size_;
    std::atomic<int>    num_done_;
    vector<std::thread> threads_;
    WorkQueue<WorkItem> work_queue_;
    vector<Vector3d>    frame_buffer_;
};

#endif