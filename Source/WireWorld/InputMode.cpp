#include "InputMode.h"

#include "WireWorld.h"

#include <iostream>

using Cell = WireWorld::Cell;

PointInputMode::PointInputMode(WireWorld& wireWorld)
    : InputMode(wireWorld)
{ }

void PointInputMode::onMousePressed(const sf::Event& e)
{
}

void PointInputMode::onMouseReleased(const sf::Event& e)
{
    auto cellLocation = m_pWireWorld->getMouseInputPosition();
    if (!cellLocation) {
        return;
    }
    auto cellInfo = m_pWireWorld->getCellPointInfo(*cellLocation);

    //Input for cell conductors
    if (e.mouseButton.button == sf::Mouse::Left) {
        if (*cellInfo.cell == Cell::Conductor || *cellInfo.cell == Cell::Empty) {
            m_pWireWorld->setCell(cellInfo.x, cellInfo.y,
                m_isInEraseMode ?
                Cell::Empty :
                Cell::Conductor);
        }
    }
    //Input for cell heads
    else if (e.mouseButton.button == sf::Mouse::Right) {
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
    if (key == sf::Keyboard::E) {
        m_isInEraseMode = !m_isInEraseMode;
        std::cout << "Erase mode toggled. Current mode: "
            << (m_isInEraseMode ? "Erase" : "Place")
            << '\n';
    }
}
