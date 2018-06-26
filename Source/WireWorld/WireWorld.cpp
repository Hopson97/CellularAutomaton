#include "WireWorld.h"

#include <iostream>
#include <cmath>
#include "../Application.h"



WireWorld::WireWorld(const Config & config, const Application& app)
    :   CellularAutomaton(config, app)
    ,   m_cells         (1280 * 720)
    ,   m_cellColours{
            config.fgColour,    //Empty 
            { 0, 191, 255 },    //Head
            { 200, 0, 0 },      //Tail
            { 255, 255, 0 } }   //Conductor
{
    std::fill(m_cells.begin(), m_cells.end(), Cell::Empty);
    m_inputGhost.setSize({ (float)config.cellSize, (float)config.cellSize });

    auto gc = m_cellColours[(int)Cell::Conductor];
    m_inputGhost.setFillColor({ gc.r, gc.g, gc.b, 200 });
}

void WireWorld::input(const sf::Event& e)
{
    if (e.type == sf::Event::KeyReleased) {
        if (e.key.code == sf::Keyboard::E) {
            m_isInEraseMode = !m_isInEraseMode;
            std::cout   << "Erase mode toggled. Current mode: " 
                        << (m_isInEraseMode ? "Erase" : "Place") 
                        << '\n';
        }
        else if (e.key.code == sf::Keyboard::L) {
            m_isInLineMode = !m_isInLineMode;
            std::cout   << "Line mode toggled. Current mode: " 
                        << (m_isInLineMode ? "Lines (Click and Hold)" : "Cells") 
                        << '\n';
        }
    }
    auto cellLocation = getMouseInputPosition();
    if (!cellLocation) {
        return;
    }

    auto pointInfo = getCellPointInfo(*cellLocation);

    //Mouse release
    if (e.type == sf::Event::MouseButtonReleased) {
        if (!m_isInLineMode) {
            mouseInput(e);
        }
        else {
            m_isDoingLineInput = false;
            m_cells.clear();
            for (auto& cellPoint : m_inputPoints) {
                auto pointInfo = getCellPointInfo(cellPoint);
                *pointInfo.cell = m_isInEraseMode ?
                                    Cell::Empty :
                                    Cell::Conductor;
                CellularAutomaton::setCellColour(pointInfo.x, pointInfo.y, m_cellColours[(int)*pointInfo.cell]);
            }
        }
    }
    else if (e.type == sf::Event::MouseButtonPressed && m_isInLineMode) {
        if (!m_isDoingLineInput) {
            m_inputBegin = { pointInfo.x, pointInfo.y };
            m_isDoingLineInput = true;
        }
    }

    if (m_isDoingLineInput) {
        m_inputEnd = { pointInfo.x, pointInfo.y };
    }
}

void WireWorld::update()
{
    if (m_isInEditMode) {
        if (m_isInLineMode && m_isDoingLineInput) {
            m_inputPoints.clear();

            int xStart = m_inputBegin.x;
            int yStart = m_inputBegin.y;

            int xEnd = m_inputEnd.x;
            int yEnd = m_inputEnd.y;
            
            std::cout << xStart << " " << m_inputEnd.x << '\n';
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
    }
    else {
        //simulate here
    }
}

WireWorld::CellPointInfo WireWorld::getCellPointInfo(const sf::Vector2i & cellPoint)
{
    CellPointInfo info;
    info.x = cellPoint.x;
    info.y = cellPoint.y;
    info.index = getCellIndex(info.x, info.y);
    info.cell = &m_cells[info.index];
    return info;
}

void WireWorld::onRenderCells(sf::RenderWindow & window)
{
    for (auto& pos : m_inputPoints) {
        float x = (float)pos.x * (float)m_pConfig->cellSize;
        float y = (float)pos.y * (float)m_pConfig->cellSize;
        m_inputGhost.setPosition(x, y);
        window.draw(m_inputGhost);
    }
}

void WireWorld::mouseInput(const sf::Event& e)
{
    auto cellLocation = getMouseInputPosition();
    if (!cellLocation) {
        return;
    }
    auto cellInfo = getCellPointInfo(*cellLocation);

    //Input for cell conductors
    if (e.mouseButton.button == sf::Mouse::Left) {
        if (*cellInfo.cell == Cell::Conductor || *cellInfo.cell == Cell::Empty) {
            *cellInfo.cell = m_isInEraseMode ?
                                Cell::Empty :
                                Cell::Conductor;
        }
    }
    //Input for cell heads
    else if (e.mouseButton.button == sf::Mouse::Right) {
        if (*cellInfo.cell == Cell::Conductor || *cellInfo.cell == Cell::Head) {
            *cellInfo.cell = m_isInEraseMode ?
                Cell::Conductor :
                Cell::Head;
        }
    }
    CellularAutomaton::setCellColour(cellInfo.x, cellInfo.y, m_cellColours[(int)*cellInfo.cell]);
}

std::optional<sf::Vector2i> WireWorld::getMouseInputPosition() const
{
    auto mousePosition = sf::Mouse::getPosition(m_pApplication->getWindow());
    auto convertedPosition = m_pApplication->getWindow().mapPixelToCoords({ (int)mousePosition.x,
        (int)mousePosition.y });
    auto x = convertedPosition.x;
    auto y = convertedPosition.y;

    if (x < 0 || x >(int)m_pConfig->windowSize.x ||
        y < 0 || y >(int)m_pConfig->windowSize.y) {
        return {};
    }

    return sf::Vector2i{
        (int)(x / m_pConfig->cellSize),
        (int)(y / m_pConfig->cellSize)
    };
}
