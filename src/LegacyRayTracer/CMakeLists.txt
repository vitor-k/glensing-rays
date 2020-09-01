add_executable(LegacyRayTracer
    RayTracer.cpp
    RungeKuttaSolver.cpp
    RungeKuttaSolver.h
    Sphere.cpp
    Sphere.h
    GravitationalEntity.cpp
    GravitationalEntity.h
    olcPixelGameEngine.h
)

create_target_directory_groups(LegacyRayTracer)

target_link_libraries(LegacyRayTracer PRIVATE common)
target_link_libraries(LegacyRayTracer PRIVATE glad)

if(NOT MSVC)
    target_link_libraries(LegacyRayTracer X11 GL pthread png)
endif()
