cmake_minimum_required(VERSION 3.11.2)

project(RayTracingDemo
        VERSION 1.0.0.0
        LANGUAGES CXX C)

# Dependencies
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/sfml)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glm)

# Project source code
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
