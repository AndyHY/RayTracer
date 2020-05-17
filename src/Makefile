CXX      = g++
CPPFLAGS = -std=c++14 -Wall

DIR      = accelerator core light material math object sampler utility
OBJECTS  = accelerator/AABB_tree.o accelerator/AABB.o \
		   core/light.o core/material.o core/object.o core/ray_tracer.o core/sampler.o core/scene.o \
		   light/area_light.o light/distant_light.o light/point_light.o \
		   material/diffuse.o material/glass.o material/glossy.o material/mirror.o \
		   math/matrix.o math/point.o math/ray.o math/utility.o math/vector.o \
		   object/plane.o object/sphere.o object/triangle_mesh.o object/triangle.o \
		   sampler/uniform_sampler.o \
		   utility/hit_record.o utility/thread_pool.o

RayTracer: $(OBJECTS) main/main.cpp
	$(CXX)  $(CPPFLAGS)  -o RayTracer $(OBJECTS) main/main.cpp -lpthread

clean:
	for dir in $(DIR); do \
		(cd $$dir && rm *.o) || continue ; \
	done
	rm RayTracer
