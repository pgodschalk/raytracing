#include "gtest/gtest.h"
#include <_stdio.h>
#include <array>
#include <cstdio>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// Helper function to execute a command and capture its output
std::string exec_command(const std::string &command) {
  std::array<char, 128> buffer;
  std::string result;

  // Open pipe to file
#if defined(_WIN32)
  std::unique_ptr<FILE, decltype(&pclose)> pipe(_popen(command.c_str(), "r"),
                                                _pclose);
#else
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"),
                                                pclose);
#endif

  if (!pipe) {
    return "ERROR";
  }

  // Read till end of process:
  while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) !=
         nullptr) {
    result += buffer.data();
  }

  return result;
}

TEST(IntegrationTest, MainProducesValidPPMOutput) {
  // Build the command to execute the raytracer
  // Adjust the path to the executable if necessary
  std::string command = "../bin/RaytracingExecutable";

  // Execute the command and capture the output
  std::string output = exec_command(command);

  // Check if the command executed successfully
  EXPECT_NE(output, "ERROR") << "Failed to execute raytracer executable.";

  // Split the output into lines
  std::istringstream iss(output);
  std::string line;
  std::vector<std::string> lines;
  while (std::getline(iss, line)) {
    lines.emplace_back(line);
  }

  // Verify PPM Header
  ASSERT_GE(lines.size(), 3)
      << "Output is too short to contain a valid PPM header.";

  EXPECT_EQ(lines[0], "P3") << "PPM header should start with 'P3'.";
  EXPECT_EQ(lines[2], "255") << "PPM max color value should be '255'.";

  // Parse image dimensions from the second line
  int width, height;
  std::istringstream dim_stream(lines[1]);
  dim_stream >> width >> height;
  EXPECT_GT(width, 0) << "Image width should be greater than 0.";
  EXPECT_GT(height, 0) << "Image height should be greater than 0.";

  // Verify that the number of pixel lines matches width * height
  size_t expected_pixel_lines = static_cast<size_t>(width * height);
  size_t actual_pixel_lines = lines.size() - 3; // Subtract header lines

  EXPECT_EQ(actual_pixel_lines, expected_pixel_lines)
      << "Number of pixel lines does not match width * height.";
}

TEST(IntegrationTest, MainProducesValidColorValues) {
  // Build the command to execute the raytracer with a small resolution
  // To facilitate testing, you might need to modify main.cc to accept
  // resolution as arguments However, since refactoring is not allowed, ensure
  // main.cc uses a known resolution

  // Execute the command and capture the output
  std::string output = exec_command(
      "../bin/RaytracingExecutable 2 1"); // Assuming main.cc can accept
                                          // width and height
  // If main.cc does not accept arguments, ensure it renders to a known
  // resolution like 400x225

  // Check if the command executed successfully
  EXPECT_NE(output, "ERROR") << "Failed to execute raytracer executable.";

  // Split the output into lines
  std::istringstream iss(output);
  std::string line;
  std::vector<std::string> lines;
  while (std::getline(iss, line)) {
    lines.emplace_back(line);
  }

  // Verify PPM Header
  ASSERT_GE(lines.size(), 3)
      << "Output is too short to contain a valid PPM header.";

  EXPECT_EQ(lines[0], "P3") << "PPM header should start with 'P3'.";
  EXPECT_EQ(lines[2], "255") << "PPM max color value should be '255'.";

  // Assuming the resolution is 2x1, verify pixel colors
  std::string expected_color = "163 200 255";
  EXPECT_EQ(lines[3], expected_color)
      << "First pixel color does not match expected.";
  EXPECT_EQ(lines[4], expected_color)
      << "Second pixel color does not match expected.";
}

TEST(IntegrationTest, OutputContainsValidNumberOfPixels) {
  // Execute the command and capture the output
  std::string output = exec_command("../bin/RaytracingExecutable");

  // Check if the command executed successfully
  EXPECT_NE(output, "ERROR") << "Failed to execute raytracer executable.";

  // Split the output into lines
  std::istringstream iss(output);
  std::string line;
  std::vector<std::string> lines;
  while (std::getline(iss, line)) {
    lines.emplace_back(line);
  }

  // Parse image dimensions from the second line
  int width, height;
  std::istringstream dim_stream(lines[1]);
  dim_stream >> width >> height;
  ASSERT_GT(width, 0);
  ASSERT_GT(height, 0);

  // Verify that the number of pixel lines matches width * height
  size_t expected_pixel_lines = static_cast<size_t>(width * height);
  size_t actual_pixel_lines = lines.size() - 3; // Subtract header lines

  EXPECT_EQ(actual_pixel_lines, expected_pixel_lines)
      << "Number of pixel lines does not match width * height.";
}
