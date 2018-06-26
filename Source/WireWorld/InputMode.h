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

        virtual void onMousePressed     (const sf::Event& e) = 0;
        virtual void onMouseReleased    (const sf::Event& e) = 0;
        virtual void onKeyPressed       (sf::Keyboard::Key key) = 0;

    protected:
        WireWorld* m_pWireWorld;
};

class PointInputMode : public InputMode
{
    public:
        PointInputMode(WireWorld& wireWorld);

        void onMousePressed(const sf::Event& e) override {}
        void onMouseReleased(const sf::Event& e) override;
        void onKeyPressed(sf::Keyboard::Key key) override;

    private:
        bool m_isInEraseMode = false;
};