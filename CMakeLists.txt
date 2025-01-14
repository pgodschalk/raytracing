cmake_minimum_required(VERSION 3.17)

# Project Name and Language
project(Raytracing
  VERSION 1.0
  DESCRIPTION "Ray Tracing in One Weekend"
  LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Specify Output Directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Enable Position-Independent Code for Libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Include subdirectories
add_subdirectory(src)
add_subdirectory(tests)

# Set default build type if not specified
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Define compiler flags based on build type
target_compile_options(RaytracingExecutable PRIVATE
  $<$<CONFIG:Debug>: -O0 -g>
  $<$<CONFIG:Release>: -O3 -DNDEBUG>
)

# Install executable
install(TARGETS RaytracingExecutable
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

# Install headers
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION include
  FILES_MATCHING PATTERN "*.h*"
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  include(CTest)
  enable_testing()
endif()
