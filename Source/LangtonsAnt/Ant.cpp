#include "Ant.h"

#include "../Util/Random.h"

namespace
{
    sf::Color getRandomColour()
    {
        uint8_t r = (uint8_t)Random::get().intInRange(0, 255);
        uint8_t g = (uint8_t)Random::get().intInRange(0, 255);
        uint8_t b = (uint8_t)Random::get().intInRange(0, 255);

        return { r, g, b };
    }
}

Ant::Ant(int xPosition, int yPosition)
:   m_position  (xPosition, yPosition)
,   m_direction (Direction(Random::get().intInRange(0, 3)))
,   m_colour    (getRandomColour())
{ }

void Ant::turn(Turn direction)
{
    int right = int(Direction::Right);
    int dir = (int)m_direction;
    switch (direction)
    {
        case Turn::Left:
            dir++;
            break;

        case Turn::Right:
            dir--;
            break;
    }

    if (dir < 0)
        dir = right;
    else if (dir > right)
        dir = 0;

    m_direction = Direction(dir);
}

void Ant::translate()
{
    switch (m_direction)
    {
        case Direction::Up:
            m_position.y--;
            break;

        case Direction::Down:
            m_position.y++;
            break;

        case Direction::Left:
            m_position.x--;
            break;

        case Direction::Right:
            m_position.x++;
            break;
    }
}
