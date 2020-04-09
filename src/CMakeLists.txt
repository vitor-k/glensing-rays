add_executable(RayTracer
    RayTracer.cpp
    RungeKuttaSolver.cpp
    RungeKuttaSolver.h
    Sphere.h
    v3d.cpp
    v3d.h
    GravitationalEntity.cpp
    GravitationalEntity.h
    olcPixelGameEngine.h
)

if(NOT MSVC)
    target_link_libraries(RayTracer X11 GL pthread png)
endif()