#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <SFML/Graphics.hpp>
struct Config
{
    Config(const sf::Vector2u& winSize, unsigned cellSize)
        : windowSize    (winSize)
        ,   cellSize    (cellSize)
    {
        windowSize.x -= windowSize.x % cellSize;
        windowSize.y -= windowSize.y % cellSize;

        simSize.x = windowSize.x / cellSize;
        simSize.y = windowSize.y / cellSize;
    }
    sf::Vector2u windowSize;
    sf::Vector2u simSize;
    unsigned cellSize;

    sf::Color bgColour;
    sf::Color fgColour;
};

#endif // CONFIG_H_INCLUDED
