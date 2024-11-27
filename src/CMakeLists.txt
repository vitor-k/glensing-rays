# Enable modules to include each other's files
include_directories(.)

add_subdirectory(common)
add_subdirectory(LegacyRayTracer)
add_subdirectory(glTests)
