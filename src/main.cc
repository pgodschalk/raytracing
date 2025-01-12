#include "raytracing/camera.h"
#include "raytracing/color.h"
#include "raytracing/hittable_list.h"
#include "raytracing/material.h"
#include "raytracing/rtweekend.h"
#include "raytracing/sphere.h"
#include "raytracing/vec3.h"
#include <cmath>

int main() {
  hittable_list world;

  auto R = std::cos(pi / 4);

  auto material_left = make_shared<lambertian>(color(0, 0, 1));
  auto material_right = make_shared<lambertian>(color(1, 0, 0));

  world.add(make_shared<sphere>(point3(-R, 0, -1), R, material_left));
  world.add(make_shared<sphere>(point3(R, 0, -1), R, material_right));

  camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;
  cam.samples_per_pixel = 100;
  cam.max_depth = 10; // Maximum number of ray bounces into scene

  cam.render(world);
}
