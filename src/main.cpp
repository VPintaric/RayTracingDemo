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

    sf::Texture rayTracerTexture;
    sf::Sprite rayTracerSprite;

    bool needToRender = true;

    sf::RenderWindow window( sf::VideoMode( 1920, 1080 ), "Ray Tracing Demo", sf::Style::Default );
    while ( window.isOpen()) {
        sf::Event event;
        while ( window.pollEvent( event )) {
            if ( event.type == sf::Event::Closed ) {
                window.close();
            }

        }

        if ( needToRender ) {
            auto image = rayTracer.render( scene, 1920, 1080 );
            rayTracerTexture.loadFromImage( image );
            rayTracerSprite.setTexture( rayTracerTexture );
            needToRender = false;
        }

        window.clear( sf::Color::White );
        window.draw( rayTracerSprite );
        window.display();
    }

    return 0;
}
