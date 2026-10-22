#pragma once

#include <SFML/Graphics/Color.hpp>

struct Colony 
{
    unsigned id= 0;
    unsigned minStrStart = 0;
    unsigned maxStrStart = 0;
    sf::Color colour;
};