//
// Created by wex on 2/16/20.
//

#include <utility/conversions.hpp>

glm::dvec3 toGlmColor( const sf::Color &c ) {
    return glm::dvec3( c.r / 255.0, c.g / 255.0, c.b / 255.0 );
}

sf::Color toSfmlColor( const glm::dvec3 &c ) {
    return sf::Color( std::min( c.r * 255, 255.0 ), std::min( c.g * 255, 255.0 ), std::min( c.b * 255, 255.0 ));
}
