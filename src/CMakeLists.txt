# src/CMakeLists.txt

# Collect all source files
set(SOURCES
  main.cc
)

# Define the executable
add_executable(RaytracingExecutable ${SOURCES})

# Include directories
target_include_directories(RaytracingExecutable
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Compiler Options
target_compile_options(RaytracingExecutable PRIVATE
  $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
  $<$<CXX_COMPILER_ID:MSVC>: /W4>
)
