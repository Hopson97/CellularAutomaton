#include "LineInputMode.h"

#include <iostream>
#include "WireWorld.h"

using Cell = WireWorld::Cell;

LineInputMode::LineInputMode(WireWorld & wireWorld)
    : InputMode(wireWorld)
{
    auto config = wireWorld.getConfig();
    m_inputGhost.setSize({ (float)config.cellSize, (float)config.cellSize });
    m_inputGhost.setFillColor({ 255, 255, 255, 100 });
}

void LineInputMode::update(const WireWorld::CellPointInfo& mousePointCellInfo)
{
    if (!m_isDoingLineInput){
        return;
    }
    m_inputEnd = { mousePointCellInfo.x, mousePointCellInfo.y };
    auto pointInfo = mousePointCellInfo;

    m_inputPoints.clear();

    int xStart = m_inputBegin.x;
    int yStart = m_inputBegin.y;

    int xEnd = m_inputEnd.x;
    int yEnd = m_inputEnd.y;
    int xDiff = std::abs(m_inputBegin.x - m_inputEnd.x);
    int yDiff = std::abs(m_inputBegin.y - m_inputEnd.y);

    if (xDiff > yDiff) {
        for (int x = std::min(xStart, xEnd); x < std::max(xStart, xEnd); x++) {
            m_inputPoints.emplace_back(x, yStart);
        }
    }
    else {
        for (int y = std::min(yStart, yEnd); y < std::max(yStart, yEnd); y++) {
            m_inputPoints.emplace_back(xStart, y);
        }
    }
}

void LineInputMode::render(sf::RenderWindow & window)
{
    auto scale = m_pWireWorld->getConfig().cellSize;
    for (auto& pos : m_inputPoints) {
        float x = (float)pos.x * scale;
        float y = (float)pos.y * scale;
        m_inputGhost.setPosition(x, y);
        window.draw(m_inputGhost);
    }
}

void LineInputMode::onMousePressed(const sf::Event & e, const WireWorld::CellPointInfo& mousePointCellInfo)
{
    if (m_isDoingLineInput) {
        return;
    }

    m_inputBegin = { mousePointCellInfo.x, mousePointCellInfo.y };
    m_isDoingLineInput = true;

    m_isPlacingConductors = e.mouseButton.button == sf::Mouse::Left;
}

void LineInputMode::onMouseReleased(const sf::Event& e, const WireWorld::CellPointInfo& mousePointCellInfo)
{
    if (!m_isDoingLineInput) return;
    for (auto& cellPoint : m_inputPoints) {
        auto pointInfo = m_pWireWorld->getCellPointInfo(cellPoint);
        if (m_isPlacingConductors) {
            m_pWireWorld->setCell(pointInfo.x,
                pointInfo.y,
                m_isInEraseMode ?
                Cell::Empty : Cell::Conductor);
        }
        else {
            auto cell = m_pWireWorld->getCell(pointInfo.x, pointInfo.y);
            if (cell == Cell::Conductor ||
                cell == Cell::Head)  {
                m_pWireWorld->setCell(pointInfo.x,
                    pointInfo.y,
                    m_isInEraseMode ?
                    Cell::Empty : Cell::Head);
            }
        }
    }
    m_isDoingLineInput = false;
    m_inputPoints.clear();
}

void LineInputMode::onKeyPressed(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::E) {
        m_isInEraseMode = !m_isInEraseMode;
        std::cout << "Erase mode toggled. Current mode: "
            << (m_isInEraseMode ? "Erase" : "Place")
            << '\n';
    }
}
