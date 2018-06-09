#ifndef ANT_H_INCLUDED
#define ANT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

//anti-clockwise order
enum class Direction
{
    Up,
    Left,
    Down,
    Right,
};

enum class Turn
{
    Left, Right
};

class Ant
{
    public:
        Ant             (int xPosition, int yPosition);

        void turn       (Turn direction);
        void translate  ();

        const sf::Vector2i& getPosition() const { return m_position; }
        void setX(int x) { m_position.x = x;    }
        void setY(int y) { m_position.y = y;    }

        sf::Color getColour () const { return m_colour; }

    private:

        sf::Vector2i    m_position;
        Direction       m_direction;
        sf::Color       m_colour;
};

#endif // ANT_H_INCLUDED
