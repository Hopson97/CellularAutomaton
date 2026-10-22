#include "PointInputMode.h"

#include <iostream>
#include "WireWorld.h"

using Cell = WireWorld::Cell;

PointInputMode::PointInputMode(WireWorld& wireWorld)
    : InputMode(wireWorld)
{ }



void PointInputMode::onMouseReleased(const sf::Event::MouseButtonReleased& e, const WireWorld::CellPointInfo& mousePointCellInfo)
{
    auto& cellInfo = mousePointCellInfo;
    //Input for cell conductors
    if (e.button == sf::Mouse::Button::Left) {
        if (*cellInfo.cell == Cell::Conductor || *cellInfo.cell == Cell::Empty) {
            m_pWireWorld->setCell(cellInfo.x, cellInfo.y,
                m_isInEraseMode ?
                Cell::Empty :
                Cell::Conductor);
        }
    }
    //Input for cell heads
    else if (e.button == sf::Mouse::Button::Right) {
        if (*cellInfo.cell == Cell::Conductor || *cellInfo.cell == Cell::Head) {
            m_pWireWorld->setCell(cellInfo.x, cellInfo.y,
                m_isInEraseMode ?
                Cell::Conductor :
                Cell::Head);
        }
    }
}

void PointInputMode::onKeyPressed(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Key::E) {
        m_isInEraseMode = !m_isInEraseMode;
        std::cout << "Erase mode toggled. Current mode: "
            << (m_isInEraseMode ? "Erase" : "Place")
            << '\n';
    }
}
