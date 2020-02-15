# Setup the targets
add_executable(RayTracingDemo
        utility/logger.hpp
        utility/logger.cpp
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
