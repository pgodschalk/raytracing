#include "raytracing/camera.h"
#include "raytracing/hittable_list.h"
#include "raytracing/rtweekend.h"
#include "raytracing/sphere.h"
#include "raytracing/vec3.h"

int main() {
  hittable_list world;

  world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

  camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;

  cam.render(world);
}
