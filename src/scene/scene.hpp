//
// Created by wex on 2/15/20.
//

#ifndef RAYTRACINGDEMO_SCENE_HPP
#define RAYTRACINGDEMO_SCENE_HPP

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <utility/logger.hpp>
#include <sfml/include/SFML/Graphics/Color.hpp>

enum class ShapeType {
    Sphere,
    Cuboid,
};

struct Sphere {
    glm::dvec3 position;
    double radius;
};

struct Cuboid {
    glm::dvec3 position;
    glm::dvec3 size;
    glm::dquat rotation;
};

struct Shape {
    ShapeType type;
    glm::dvec3 color;
    double reflectiveness;
    union {
        Sphere sphere;
        Cuboid cuboid;
    };
};

struct Light {
    glm::dvec3 position;
    glm::dvec3 color;
};

struct Scene {
    std::vector< Shape > shapes;
    std::vector< Light > lights;
    glm::dvec3 cameraPosition;
    glm::dvec3 cameraDirection;
    double widthFieldOfView; // radians
    double heightFieldOfView; // radians
};

#endif //RAYTRACINGDEMO_SCENE_HPP
