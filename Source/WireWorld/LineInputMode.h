#pragma once

#include "InputMode.h"

class LineInputMode : public InputMode
{
    public:
        LineInputMode(WireWorld& wireWorld);

        void update             (const WireWorld::CellPointInfo& mousePointCellInfo) override;
        void render             (sf::RenderWindow& window) override;
        void onMousePressed     (const sf::Event& e, const WireWorld::CellPointInfo& mousePointCellInfo) override;
        void onMouseReleased    (const sf::Event& e, const WireWorld::CellPointInfo& mousePointCellInfo) override;
        void onKeyPressed       (sf::Keyboard::Key key) override;

    private:
        sf::Vector2i m_inputBegin;
        sf::Vector2i m_inputEnd;
        std::vector<sf::Vector2i> m_inputPoints;
        sf::RectangleShape m_inputGhost;
        
        bool m_isPlacingConductors = true;
        bool m_isInEraseMode = false;
        bool m_isDoingLineInput = false;
};