# Setup the targets
add_executable(RayTracingDemo
        raytracer/ray_tracer.cpp
        raytracer/ray_tracer.hpp
        scene/scene.hpp
        utility/conversions.cpp
        utility/conversions.hpp
        utility/logger.cpp
        utility/logger.hpp
        main.cpp)

target_link_libraries(RayTracingDemo
        PRIVATE
        sfml-window
        sfml-graphics
        sfml-system
        glm)

target_include_directories(RayTracingDemo
        PUBLIC ../external
        PRIVATE ../src)

target_compile_features(RayTracingDemo
        PUBLIC cxx_std_17)

target_compile_options(RayTracingDemo
        PRIVATE -Wall -Werror)
