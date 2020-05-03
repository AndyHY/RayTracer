CXX      = g++
CPPFLAGS = -std=c++11 -Wall

DIR      = core light material math object utility
OBJECTS  = core/light.o core/material.o core/object.o core/ray_tracer.o core/sampler.o core/scene.o \
		   light/distant_light.o light/point_light.o \
		   material/diffuse.o material/glass.o material/glossy.o material/mirror.o \
		   math/matrix.o math/point.o math/ray.o math/utility.o math/vector.o \
		   object/plane.o object/sphere.o object/triangle.o \
		   utility/hit_record.o

RayTracer: $(OBJECTS) main/main.cpp
	$(CXX) $(CPPFLAGS) -o RayTracer $(OBJECTS) main/main.cpp

clean:
	for dir in $(DIR); do \
		(cd $$dir && rm *.o) || continue ; \
	done
	rm RayTracer
