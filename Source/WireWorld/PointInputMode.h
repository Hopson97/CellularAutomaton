#pragma once

#include "InputMode.h"

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