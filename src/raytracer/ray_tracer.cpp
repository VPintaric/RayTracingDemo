//
// Created by wex on 2/15/20.
//

#include <raytracer/ray_tracer.hpp>

RayTracer::RayTracer( Logger &logger ) : logger_( logger ) {

}

RayTracer::~RayTracer() = default;

sf::Image RayTracer::render( const Scene &scene, unsigned width, unsigned height ) {
    sf::Image image;
    image.create( width, height, sf::Color::Black );

    return image;
}
