#pragma once

#include <SFML/Graphics.hpp>

class WireWorld;

class InputMode
{
    public:
        InputMode(WireWorld& wireWorld)
            : m_pWireWorld(&wireWorld)
        { }
        virtual ~InputMode() = default;

        virtual void update             () {}
        virtual void render             (sf::RenderWindow& window) {}
        virtual void onMousePressed     (const sf::Event& e) = 0;
        virtual void onMouseReleased    (const sf::Event& e) = 0;
        virtual void onKeyPressed       (sf::Keyboard::Key key) = 0;

    protected:
        WireWorld* m_pWireWorld;
};

