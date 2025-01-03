#include <array>
#include <cstdio>
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <string>

// Helper function to execute a command and capture its output
std::string exec_command(const std::string &cmd) {
  std::array<char, 4096> buffer;
  std::string result;

  // Open pipe to file
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"),
                                                pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }

  // Read till end of process:
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }

  return result;
}

// Test the PPM header
TEST(IntegrationTest, PPMHeader) {
  // Command to execute the application
  std::string command = "../bin/RaytracingExecutable";

  // Execute and capture output
  std::string output = exec_command(command);

  // Parse the header
  std::istringstream iss(output);
  std::string magic;
  int width, height, max_val;
  iss >> magic >> width >> height >> max_val;

  EXPECT_EQ(magic, "P3");
  EXPECT_EQ(width, 256);
  EXPECT_EQ(height, 256);
  EXPECT_EQ(max_val, 255);
}

// Test specific pixel values
TEST(IntegrationTest, PixelValues) {
  std::string command = "../bin/RaytracingExecutable";
  std::string output = exec_command(command);

  // Skip header
  std::istringstream iss(output);
  std::string magic;
  int width, height, max_val;
  iss >> magic >> width >> height >> max_val;

  // Read first pixel (top-left)
  int r0, g0, b0;
  iss >> r0 >> g0 >> b0;
  EXPECT_EQ(r0, 0);
  EXPECT_EQ(g0, 0);
  EXPECT_EQ(b0, 0);

  // Read last pixel (bottom-right)
  int rl, gl, bl;
  // Move to the last line
  std::string line;
  while (std::getline(iss, line)) { /* Iterate to the end */
  }
  // Re-open the stream to read the last pixel
  iss.clear();
  iss.seekg(0, std::ios::beg);
  // Skip header
  iss >> magic >> width >> height >> max_val;
  // Read all pixels and keep the last one
  while (iss >> rl >> gl >> bl) { /* Keep iterating */
  }
  EXPECT_EQ(rl, 255);
  EXPECT_EQ(gl, 255);
  EXPECT_EQ(bl, 0);
}

// Test a middle pixel, e.g., (128, 128)
TEST(IntegrationTest, MiddlePixelValue) {
  std::string command = "../bin/RaytracingExecutable";
  std::string output = exec_command(command);

  std::istringstream iss(output);
  std::string magic;
  int width, height, max_val;
  iss >> magic >> width >> height >> max_val;

  // Calculate the index for (128, 128)
  int target_i = 128;
  int target_j = 128;
  int target_index = target_j * width + target_i;

  int current_index = 0;
  int r_mid, g_mid, b_mid;
  while (iss >> r_mid >> g_mid >> b_mid) {
    if (current_index == target_index) {
      break;
    }
    current_index++;
  }

  EXPECT_NEAR(r_mid, 128, 1);
  EXPECT_NEAR(g_mid, 128, 1);
  EXPECT_EQ(b_mid, 0);
}

// Test the total number of pixels
TEST(IntegrationTest, TotalPixels) {
  std::string command = "../bin/RaytracingExecutable";
  std::string output = exec_command(command);

  std::istringstream iss(output);
  std::string magic;
  int width, height, max_val;
  iss >> magic >> width >> height >> max_val;

  int pixel_count = 0;
  int r, g, b;
  while (iss >> r >> g >> b) {
    pixel_count++;
  }

  EXPECT_EQ(pixel_count, width * height);
}

// Main function for Google Test
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
