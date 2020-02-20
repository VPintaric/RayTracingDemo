//
// Created by wex on 2/15/20.
//

#include <raytracer/ray_tracer.hpp>
#include <utility/conversions.hpp>

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/intersect.hpp>

RayTracer::RayTracer( Logger &logger ) : logger_( logger ) {

}

RayTracer::~RayTracer() = default;

sf::Image RayTracer::render( const Scene &scene, unsigned width, unsigned height ) {
    sf::Image image;
    image.create( width, height, sf::Color::Black );

    auto pixelRay = scene.cameraDirection;
    pixelRay = glm::rotate( pixelRay, -scene.widthFieldOfView / 2.0, up_ );
    pixelRay = glm::rotate( pixelRay, -scene.heightFieldOfView / 2.0, glm::cross( up_, pixelRay ));

    auto fovWidthPerPixel = scene.widthFieldOfView / width;
    auto fovHeightPerPixel = scene.heightFieldOfView / height;

    for ( unsigned j = 0; j < height; ++j ) {
        pixelRay = glm::rotate( pixelRay, fovHeightPerPixel, glm::cross( up_, pixelRay ));

        for ( unsigned i = 0; i < width; ++i ) {
            pixelRay = glm::rotate( pixelRay, fovWidthPerPixel, up_ );

            image.setPixel( i, j, toSfmlColor( generateColor( scene, scene.cameraPosition, pixelRay )));
        }

        pixelRay = glm::rotate( pixelRay, -scene.widthFieldOfView, up_ );
    }

    return image;
}

glm::dvec3 RayTracer::generateColor( const Scene &scene, const glm::dvec3 &rayOrigin,
                                     const glm::dvec3 &rayDirection ) const {

    auto[color, background] = rayTrace( scene, rayOrigin, rayDirection, 1 );

    if ( background ) {
        return glm::dvec3{};
    } else {
        return color;
    }
}

std::pair< glm::dvec3, bool > RayTracer::rayTrace( const Scene &scene,
                                                   const glm::dvec3 &rayOrigin, const glm::dvec3 &rayDirection,
                                                   const int traceDepth ) const {

    if ( traceDepth == 0 ) {
        return std::make_pair( glm::dvec3{}, true );
    }

    bool foundIntersection = false;
    double intersectionDistance;
    glm::dvec3 intersectionNormal;
    const Shape *intersectionShape;

    for ( const auto &shape : scene.shapes ) {
        auto[intersected, distance, normal] = checkCollision( shape, rayOrigin, rayDirection );

        if ( intersected && ( !foundIntersection || distance < intersectionDistance )) {
            foundIntersection = true;
            intersectionDistance = distance;
            intersectionNormal = normal;
            intersectionShape = &shape;
        }
    }

    if ( foundIntersection ) {
        auto intersectionPoint = rayOrigin + intersectionDistance * rayDirection;
        glm::dvec3 color{};

//        auto reflectedRay = glm::reflect( rayDirection, intersectionNormal );

        for ( const auto &light : scene.lights ) {
            if ( !isShadowed( scene, light, intersectionPoint )) {
                auto towardsLight = glm::normalize( light.position - intersectionPoint );

                auto diffuseIntensity = std::max( glm::dot( towardsLight, intersectionNormal ), 0.0 );
                auto diffuseColor = diffuseIntensity * light.color * intersectionShape->color;

                // TODO: add reflected color and/or specular

                color += diffuseColor;
            }
        }

        return std::make_pair( color, false );
    }

    return std::make_pair( glm::dvec3{}, true );
}

std::tuple< bool, double, glm::dvec3 > RayTracer::checkCollision( const Shape &shape, const glm::dvec3 &rayOrigin,
                                                                  const glm::dvec3 &rayDirection ) const {

    double intersectionDistance{};
    glm::dvec3 normal{};
    bool isIntersection = false;

    if ( shape.type == ShapeType::Sphere ) {
        isIntersection = glm::intersectRaySphere( rayOrigin, rayDirection, shape.sphere.position,
                                                  shape.sphere.radius * shape.sphere.radius,
                                                  intersectionDistance );
        intersectionDistance -= intersectionTolerance_;

        normal = glm::normalize( rayOrigin + intersectionDistance * rayDirection - shape.sphere.position );
    } else if ( shape.type == ShapeType::Cuboid ) {
        // TODO

        intersectionDistance -= intersectionTolerance_;
    }

    return std::make_tuple( isIntersection, intersectionDistance, normal );
}

bool RayTracer::isShadowed( const Scene &scene, const Light &light, const glm::dvec3 &point ) const {
    auto direction = glm::normalize( light.position - point );

    for ( const auto &shape : scene.shapes ) {
        auto[intersected, distance, normal] = checkCollision( shape, point, direction );

        if ( intersected ) {
            return true;
        }
    }
    return false;
}
