//
// Created by wex on 2/15/20.
//

#ifndef RAYTRACINGDEMO_RAY_TRACER_HPP
#define RAYTRACINGDEMO_RAY_TRACER_HPP

#include <SFML/Graphics.hpp>

#include <scene/scene.hpp>

class RayTracer {
public:
    explicit RayTracer( Logger &logger );

    ~RayTracer();

    sf::Image render( const Scene &scene, unsigned width, unsigned height );

private:
    static constexpr glm::dvec3 up_{ 0.0, 1.0, 0.0 };
    static constexpr double intersectionTolerance_{ 0.000001 };

    Logger &logger_;

    sf::Color rayTrace( const Scene &scene, const glm::dvec3 &rayOrigin, const glm::dvec3 &rayDirection ) const;

    std::tuple< bool, double, glm::dvec3 >
    checkCollision( const Shape &shape, const glm::dvec3 &rayOrigin, const glm::dvec3 &rayDirection ) const;

    bool isShadowed( const Scene &scene, const Light &light, const glm::dvec3 &point ) const;
};

#endif //RAYTRACINGDEMO_RAY_TRACER_HPP
