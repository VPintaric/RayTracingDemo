//
// Created by wex on 2/15/20.
//

#include <cstdio>

#include <SFML/Graphics.hpp>

#include <utility/logger.hpp>
#include <raytracer/ray_tracer.hpp>

int main() {
    Logger logger;
    RayTracer rayTracer( logger );
    Scene scene;

    constexpr int windowWidth = 1920;
    constexpr int windowHeight = 1080;
    constexpr int rendererWidth = 1920;
    constexpr int rendererHeight = 1080;

    ///////////////// SCENE SETUP //////////////////
    {
        {
            Shape shape;
            shape.type = ShapeType::Sphere;
            shape.color = sf::Color::Red;
            shape.sphere.position = glm::dvec3{ 1.0, 2.0, 3.0 };
            shape.sphere.radius = 10.0;
            scene.shapes.push_back( shape );
        }

        {
            Light light;
            light.color = sf::Color::Blue;
            light.position = glm::dvec3{ 1.0, 20.0, 3.0 };
        }

        scene.cameraPosition = glm::dvec3{ 18.0, 2.0, 3.0 };
        scene.cameraDirection = glm::normalize( glm::dvec3{ -11.0, 0.0, 0.0 } );
        scene.heightFieldOfView = glm::radians( 60.0 );
        scene.widthFieldOfView = glm::radians( 90.0 );
    }
    ////////////////////////////////////////////////

    sf::Texture rayTracerTexture;
    sf::Sprite rayTracerSprite;

    bool needToRender = true;

    sf::RenderWindow window( sf::VideoMode( windowWidth, windowHeight ), "Ray Tracing Demo", sf::Style::Default );
    while ( window.isOpen()) {
        sf::Event event;
        while ( window.pollEvent( event )) {
            if ( event.type == sf::Event::Closed ) {
                window.close();
            }

        }

        if ( needToRender ) {
            auto image = rayTracer.render( scene, rendererWidth, rendererHeight );
            rayTracerTexture.loadFromImage( image );
            rayTracerSprite.setTexture( rayTracerTexture );
            rayTracerSprite.setScale( static_cast<float>(windowWidth) / rendererWidth,
                                      static_cast<float>(windowHeight) / rendererHeight );
            needToRender = false;
        }

        window.clear( sf::Color::White );
        window.draw( rayTracerSprite );
        window.display();
    }

    return 0;
}
