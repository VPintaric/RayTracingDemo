//
// Created by wex on 2/15/20.
//

#ifndef RAYTRACINGDEMO_RAY_TRACER_HPP
#define RAYTRACINGDEMO_RAY_TRACER_HPP

#include <SFML/Graphics.hpp>

#include <scene/scene.hpp>

class RayTracer {
public:
    explicit RayTracer(Logger &logger);

    ~RayTracer();

    sf::Image render( const Scene &scene, unsigned width, unsigned height );

private:
    Logger &logger_;

};

#endif //RAYTRACINGDEMO_RAY_TRACER_HPP
