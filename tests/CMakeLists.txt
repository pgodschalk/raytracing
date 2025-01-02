# tests/CMakeLists.txt

# Enable testing
enable_testing()

# Download and unpack googletest at configure time
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.15.2.tar.gz
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add test executable
file(GLOB_RECURSE TEST_SOURCES "*.cpp" "*.cxx" "*.cc")

add_executable(RaytracingTests ${TEST_SOURCES})

# Link test libraries
target_link_libraries(RaytracingTests
  PRIVATE
    gtest_main
    MyProjectExecutable # If needed
)

# Include directories
target_include_directories(RaytracingTests
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

# Register tests
include(GoogleTest)
gtest_discover_tests(RaytracingTests)
