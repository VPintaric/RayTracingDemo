//
// Created by wex on 2/16/20.
//

#ifndef RAYTRACINGDEMO_CONVERSIONS_HPP
#define RAYTRACINGDEMO_CONVERSIONS_HPP

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>

glm::dvec3 toGlmColor( const sf::Color &c );

sf::Color toSfmlColor( const glm::dvec3 &c );

#endif //RAYTRACINGDEMO_CONVERSIONS_HPP
