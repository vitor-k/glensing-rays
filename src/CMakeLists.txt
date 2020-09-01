add_executable(RayTracer
    RayTracer.cpp
    RungeKuttaSolver.cpp
    RungeKuttaSolver.h
    Sphere.cpp
    Sphere.h
    v3d.cpp
    v3d.h
    GravitationalEntity.cpp
    GravitationalEntity.h
    olcPixelGameEngine.h
)

create_target_directory_groups(RayTracer)

target_link_libraries(RayTracer PRIVATE glad)

if(NOT MSVC)
    target_link_libraries(RayTracer X11 GL pthread png)
endif()