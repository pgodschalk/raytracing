#include "raytracing/camera.h"
#include "raytracing/hittable.h"
#include "raytracing/hittable_list.h"
#include "raytracing/interval.h"
#include "raytracing/ray.h"
#include "raytracing/vec3.h"
#include <cfloat>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <streambuf>
#include <string>
#include <vector>

// Place all helper classes and functions inside an anonymous namespace
namespace {

// Concrete hittable that never hits anything
class HittableNone : public hittable {
public:
  virtual bool hit(const ray &r, interval ray_t,
                   hit_record &rec) const override {
    return false;
  }
};

// Concrete hittable that always hits with a fixed normal
class HittableAlwaysHit : public hittable {
public:
  virtual bool hit(const ray &r, interval ray_t,
                   hit_record &rec) const override {
    rec.p = point3(0, 0, -1);
    rec.normal = vec3(0, 0, 1);
    rec.t = 1.0;
    rec.set_face_normal(r, rec.normal);
    return true;
  }
};

// A simple hittable implementation for additional testing
class test_hittable : public hittable {
public:
  bool should_hit;
  float hit_t;

  test_hittable(bool hit = false, float t = 0.0f) : should_hit(hit), hit_t(t) {}

  virtual bool hit(const ray &r, interval ray_t,
                   hit_record &rec) const override {
    if (should_hit && ray_t.min <= hit_t && hit_t <= ray_t.max) {
      rec.t = hit_t;
      return true;
    }
    return false;
  }
};

} // anonymous namespace

// Test fixture for camera
class CameraTest : public ::testing::Test {
protected:
  camera cam;

  void SetUp() override {
    // Default settings can be modified in individual tests
  }
};

// Test image height calculation based on aspect ratio
TEST_F(CameraTest, ImageHeightCalculation) {
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 1920;

  HittableNone world;

  std::stringstream ss;
  std::streambuf *original_cout = std::cout.rdbuf(ss.rdbuf());

  cam.render(world);

  std::cout.rdbuf(original_cout);

  // Check PPM header
  std::string expected_header = "P3\n1920 1080\n255\n";
  std::string actual_header = ss.str().substr(0, expected_header.size());
  EXPECT_EQ(actual_header, expected_header);
}

// Test render output when no objects are hit (background color)
TEST_F(CameraTest, RenderBackgroundColor) {
  cam.aspect_ratio = 1.0;
  cam.image_width = 2;
  HittableNone world;

  std::stringstream ss;
  std::streambuf *original_cout = std::cout.rdbuf(ss.rdbuf());

  cam.render(world);

  std::cout.rdbuf(original_cout);

  // Expected PPM header
  std::string expected_header = "P3\n2 2\n255\n";
  std::string actual_header = ss.str().substr(0, expected_header.size());
  EXPECT_EQ(actual_header, expected_header);

  // Extract color data
  std::istringstream iss(ss.str());
  std::string header;
  iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // P3
  iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // dimensions
  iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // max color

  std::vector<std::string> colors;
  std::string color;
  while (iss >> color) {
    colors.push_back(color);
  }

  // Each pixel should have 3 color components
  ASSERT_EQ(colors.size(), 2 * 2 * 3);

  // Since no objects are hit, pixels should have background colors based on ray
  // direction. This typically results in a gradient, but exact values depend on
  // camera setup. Here we verify that color components are within valid range
  // [0, 255]
  for (const auto &c : colors) {
    int value = std::stoi(c);
    EXPECT_GE(value, 0);
    EXPECT_LE(value, 255);
  }
}

// Test camera initialization with different aspect ratios
TEST_F(CameraTest, InitializeDifferentAspectRatios) {
  cam.image_width = 4;

  struct AspectRatioTestCase {
    double aspect_ratio;
    int expected_height;
  };

  std::vector<AspectRatioTestCase> test_cases = {
      {1.0, 4}, {16.0 / 9.0, 2}, {2.0, 2},   {0.5, 8}, {0.25, 16},
      {3.0, 1}, {1.5, 2},        {1.333, 3}, {0.75, 5}};

  for (const auto &test_case : test_cases) {
    cam.aspect_ratio = test_case.aspect_ratio;
    HittableNone world;

    std::stringstream ss;
    std::streambuf *original_cout = std::cout.rdbuf(ss.rdbuf());

    cam.render(world);

    std::cout.rdbuf(original_cout);

    // Construct expected PPM header
    std::ostringstream expected_header_stream;
    expected_header_stream << "P3\n"
                           << cam.image_width << " "
                           << test_case.expected_height << "\n255\n";
    std::string expected_header = expected_header_stream.str();

    // Check PPM header
    std::string actual_header = ss.str().substr(0, expected_header.size());
    EXPECT_EQ(actual_header, expected_header);
  }
}

// Test that render handles image_width of 0 gracefully
TEST_F(CameraTest, RenderWithZeroImageWidth) {
  cam.image_width = 0;
  cam.aspect_ratio = 1.0;
  HittableNone world;

  std::stringstream ss;
  std::streambuf *original_cout = std::cout.rdbuf(ss.rdbuf());

  cam.render(world);

  std::cout.rdbuf(original_cout);

  // Image height should be clamped to 1
  std::string expected_header = "P3\n0 1\n255\n";
  std::string actual_header = ss.str().substr(0, expected_header.size());
  EXPECT_EQ(actual_header, expected_header);
}

// Test that image_height is clamped to at least 1
TEST_F(CameraTest, ImageHeightClampedToOne) {
  cam.image_width = 1;
  cam.aspect_ratio = 2.0; // image_height = 0.5 -> should clamp to 1
  HittableNone world;

  std::stringstream ss;
  std::streambuf *original_cout = std::cout.rdbuf(ss.rdbuf());

  cam.render(world);

  std::cout.rdbuf(original_cout);

  // Check PPM header
  std::string expected_header = "P3\n1 1\n255\n";
  std::string actual_header = ss.str().substr(0, expected_header.size());
  EXPECT_EQ(actual_header, expected_header);
}

// Test camera with very high aspect ratio
TEST_F(CameraTest, HighAspectRatio) {
  cam.image_width = 100;
  cam.aspect_ratio = 100.0; // image_height = 1
  HittableNone world;

  std::stringstream ss;
  std::streambuf *original_cout = std::cout.rdbuf(ss.rdbuf());

  cam.render(world);

  std::cout.rdbuf(original_cout);

  // Check PPM header
  std::string expected_header = "P3\n100 1\n255\n";
  std::string actual_header = ss.str().substr(0, expected_header.size());
  EXPECT_EQ(actual_header, expected_header);
}

// Test camera with very low aspect ratio
TEST_F(CameraTest, LowAspectRatio) {
  cam.image_width = 1;
  cam.aspect_ratio = 0.1; // image_height = 10
  HittableNone world;

  std::stringstream ss;
  std::streambuf *original_cout = std::cout.rdbuf(ss.rdbuf());

  cam.render(world);

  std::cout.rdbuf(original_cout);

  // Check PPM header
  std::string expected_header = "P3\n1 10\n255\n";
  std::string actual_header = ss.str().substr(0, expected_header.size());
  EXPECT_EQ(actual_header, expected_header);
}

// Helper function to compare two vec3 objects with a tolerance
bool Vec3AlmostEqual(const vec3 &v1, const vec3 &v2, double tol = 1e-8) {
  return (std::abs(v1.x() - v2.x()) < tol) &&
         (std::abs(v1.y() - v2.y()) < tol) && (std::abs(v1.z() - v2.z()) < tol);
}

// Test fixture for hit_record
class HitRecordTest : public ::testing::Test {
protected:
  hit_record rec;
  ray r;
  vec3 outward_normal;
};

// Test set_face_normal when the ray hits the front face
TEST_F(HitRecordTest, SetFaceNormal_FrontFace) {
  // Ray pointing in the -z direction
  r = ray(point3(0, 0, 0), vec3(0, 0, -1));
  // Outward normal pointing in the +z direction
  outward_normal = vec3(0, 0, 1);

  rec.set_face_normal(r, outward_normal);

  EXPECT_TRUE(rec.front_face);
  EXPECT_TRUE(Vec3AlmostEqual(rec.normal, outward_normal));
}

// Test set_face_normal when the ray hits the back face
TEST_F(HitRecordTest, SetFaceNormal_BackFace) {
  // Ray pointing in the +z direction
  r = ray(point3(0, 0, 0), vec3(0, 0, 1));
  // Outward normal pointing in the +z direction
  outward_normal = vec3(0, 0, 1);

  rec.set_face_normal(r, outward_normal);

  EXPECT_FALSE(rec.front_face);
  vec3 expected_normal = -outward_normal;
  EXPECT_TRUE(Vec3AlmostEqual(rec.normal, expected_normal));
}

// Test set_face_normal with a ray parallel to the normal
TEST_F(HitRecordTest, SetFaceNormal_ParallelRay) {
  // Ray parallel to the outward normal, pointing in the same direction
  r = ray(point3(0, 0, 0), vec3(0, 0, 1));
  // Outward normal pointing in the +z direction
  outward_normal = vec3(0, 0, 1);

  rec.set_face_normal(r, outward_normal);

  EXPECT_FALSE(rec.front_face);
  vec3 expected_normal = -outward_normal;
  EXPECT_TRUE(Vec3AlmostEqual(rec.normal, expected_normal));
}

// Test set_face_normal with a ray perpendicular to the normal
TEST_F(HitRecordTest, SetFaceNormal_PerpendicularRay) {
  // Ray perpendicular to the outward normal
  r = ray(point3(0, 0, 0), vec3(1, 0, 0));
  // Outward normal pointing in the +z direction
  outward_normal = vec3(0, 0, 1);

  rec.set_face_normal(r, outward_normal);

  EXPECT_FALSE(rec.front_face);
  vec3 expected_normal = -outward_normal;
  EXPECT_TRUE(Vec3AlmostEqual(rec.normal, expected_normal));
}

// Test set_face_normal with zero direction ray
TEST_F(HitRecordTest, SetFaceNormal_ZeroDirectionRay) {
  // Ray with zero direction
  r = ray(point3(0, 0, 0), vec3(0, 0, 0));
  // Outward normal pointing in the +z direction
  outward_normal = vec3(0, 0, 1);

  rec.set_face_normal(r, outward_normal);

  // Since dot product is zero, front_face should be false
  EXPECT_FALSE(rec.front_face);
  vec3 expected_normal = -outward_normal;
  EXPECT_TRUE(Vec3AlmostEqual(rec.normal, expected_normal));
}

// HittableList Tests

TEST(HittableListTest, InitiallyEmpty) {
  hittable_list list;
  EXPECT_TRUE(list.objects.empty());
}

TEST(HittableListTest, AddObject) {
  hittable_list list;
  // Define the helper class within this test's anonymous namespace
  class LocalTestHittable : public hittable {
  public:
    bool should_hit;
    float hit_t;

    LocalTestHittable(bool hit = false, float t = 0.0f)
        : should_hit(hit), hit_t(t) {}

    virtual bool hit(const ray &r, interval ray_t,
                     hit_record &rec) const override {
      if (should_hit && ray_t.min <= hit_t && hit_t <= ray_t.max) {
        rec.t = hit_t;
        return true;
      }
      return false;
    }
  };

  auto obj = std::make_shared<LocalTestHittable>();
  list.add(obj);
  ASSERT_EQ(list.objects.size(), 1);
  EXPECT_EQ(list.objects[0], obj);
}

TEST(HittableListTest, ClearObjects) {
  hittable_list list;

  // Define the helper class within this test's anonymous namespace
  class LocalTestHittable : public hittable {
  public:
    bool should_hit;
    float hit_t;

    LocalTestHittable(bool hit = false, float t = 0.0f)
        : should_hit(hit), hit_t(t) {}

    virtual bool hit(const ray &r, interval ray_t,
                     hit_record &rec) const override {
      if (should_hit && ray_t.min <= hit_t && hit_t <= ray_t.max) {
        rec.t = hit_t;
        return true;
      }
      return false;
    }
  };

  list.add(std::make_shared<LocalTestHittable>());
  list.add(std::make_shared<LocalTestHittable>());
  EXPECT_EQ(list.objects.size(), 2);
  list.clear();
  EXPECT_TRUE(list.objects.empty());
}

TEST(HittableListTest, HitEmptyList) {
  hittable_list list;

  // Empty hittable_list should not hit anything
  ray r;
  interval t(0.0f, FLT_MAX);
  hit_record rec;
  EXPECT_FALSE(list.hit(r, t, rec));
}

TEST(HittableListTest, HitSingleObject) {
  hittable_list list;

  // Define the helper class within this test's anonymous namespace
  class LocalTestHittable : public hittable {
  public:
    bool should_hit;
    float hit_t;

    LocalTestHittable(bool hit = false, float t = 0.0f)
        : should_hit(hit), hit_t(t) {}

    virtual bool hit(const ray &r, interval ray_t,
                     hit_record &rec) const override {
      if (should_hit && ray_t.min <= hit_t && hit_t <= ray_t.max) {
        rec.t = hit_t;
        return true;
      }
      return false;
    }
  };

  auto obj = std::make_shared<LocalTestHittable>(true, 5.0f);
  list.add(obj);

  ray r;
  interval t(0.0f, 10.0f);
  hit_record rec;
  EXPECT_TRUE(list.hit(r, t, rec));
  EXPECT_EQ(rec.t, 5.0f);
}

TEST(HittableListTest, HitMultipleObjectsClosestFirst) {
  hittable_list list;

  // Define helper classes within an anonymous namespace
  class LocalTestHittable : public hittable {
  public:
    bool should_hit;
    float hit_t;

    LocalTestHittable(bool hit = false, float t = 0.0f)
        : should_hit(hit), hit_t(t) {}

    virtual bool hit(const ray &r, interval ray_t,
                     hit_record &rec) const override {
      if (should_hit && ray_t.min <= hit_t && hit_t <= ray_t.max) {
        rec.t = hit_t;
        return true;
      }
      return false;
    }
  };

  auto obj1 = std::make_shared<LocalTestHittable>(true, 5.0f);
  auto obj2 = std::make_shared<LocalTestHittable>(true, 3.0f);
  list.add(obj1);
  list.add(obj2);

  ray r;
  interval t(0.0f, 10.0f);
  hit_record rec;
  EXPECT_TRUE(list.hit(r, t, rec));
  EXPECT_EQ(rec.t, 3.0f);
}

TEST(HittableListTest, HitMultipleObjectsClosestLast) {
  hittable_list list;

  // Define helper classes within an anonymous namespace
  class LocalTestHittable : public hittable {
  public:
    bool should_hit;
    float hit_t;

    LocalTestHittable(bool hit = false, float t = 0.0f)
        : should_hit(hit), hit_t(t) {}

    virtual bool hit(const ray &r, interval ray_t,
                     hit_record &rec) const override {
      if (should_hit && ray_t.min <= hit_t && hit_t <= ray_t.max) {
        rec.t = hit_t;
        return true;
      }
      return false;
    }
  };

  auto obj1 = std::make_shared<LocalTestHittable>(true, 5.0f);
  auto obj2 = std::make_shared<LocalTestHittable>(true, 7.0f);
  list.add(obj1);
  list.add(obj2);

  ray r;
  interval t(0.0f, 10.0f);
  hit_record rec;
  EXPECT_TRUE(list.hit(r, t, rec));
  EXPECT_EQ(rec.t, 5.0f);
}

TEST(HittableListTest, NoHitWhenObjectsDoNotHit) {
  hittable_list list;

  // Define helper classes within an anonymous namespace
  class LocalTestHittable : public hittable {
  public:
    bool should_hit;
    float hit_t;

    LocalTestHittable(bool hit = false, float t = 0.0f)
        : should_hit(hit), hit_t(t) {}

    virtual bool hit(const ray &r, interval ray_t,
                     hit_record &rec) const override {
      if (should_hit && ray_t.min <= hit_t && hit_t <= ray_t.max) {
        rec.t = hit_t;
        return true;
      }
      return false;
    }
  };

  auto obj1 = std::make_shared<LocalTestHittable>(false);
  auto obj2 = std::make_shared<LocalTestHittable>(false);
  list.add(obj1);
  list.add(obj2);

  ray r;
  interval t(0.0f, 10.0f);
  hit_record rec;
  EXPECT_FALSE(list.hit(r, t, rec));
}

TEST(HittableListTest, HitWithinInterval) {
  hittable_list list;

  // Define helper classes within an anonymous namespace
  class LocalTestHittable : public hittable {
  public:
    bool should_hit;
    float hit_t;

    LocalTestHittable(bool hit = false, float t = 0.0f)
        : should_hit(hit), hit_t(t) {}

    virtual bool hit(const ray &r, interval ray_t,
                     hit_record &rec) const override {
      if (should_hit && ray_t.min <= hit_t && hit_t <= ray_t.max) {
        rec.t = hit_t;
        return true;
      }
      return false;
    }
  };

  auto obj1 = std::make_shared<LocalTestHittable>(true, 15.0f);
  auto obj2 = std::make_shared<LocalTestHittable>(true, 5.0f);
  list.add(obj1);
  list.add(obj2);

  ray r;
  interval t(0.0f, 10.0f);
  hit_record rec;
  EXPECT_TRUE(list.hit(r, t, rec));
  EXPECT_EQ(rec.t, 5.0f);
}

TEST(HittableListTest, HitOutsideInterval) {
  hittable_list list;

  // Define helper classes within an anonymous namespace
  class LocalTestHittable : public hittable {
  public:
    bool should_hit;
    float hit_t;

    LocalTestHittable(bool hit = false, float t = 0.0f)
        : should_hit(hit), hit_t(t) {}

    virtual bool hit(const ray &r, interval ray_t,
                     hit_record &rec) const override {
      if (should_hit && ray_t.min <= hit_t && hit_t <= ray_t.max) {
        rec.t = hit_t;
        return true;
      }
      return false;
    }
  };

  auto obj = std::make_shared<LocalTestHittable>(true, 15.0f);
  list.add(obj);

  ray r;
  interval t(0.0f, 10.0f);
  hit_record rec;
  EXPECT_FALSE(list.hit(r, t, rec));
}
