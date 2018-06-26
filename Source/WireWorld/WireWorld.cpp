#include "WireWorld.h"

#include <iostream>
#include <cmath>
#include "../Application.h"

#include "PointInputMode.h"
#include "LineInputMode.h"


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

    m_inputMode = std::make_unique<LineInputMode>(*this);
}

void WireWorld::input(const sf::Event& e)
{
    if (e.type == sf::Event::KeyReleased) {
        m_inputMode->onKeyPressed(e.key.code);
        /*
        if (e.key.code == sf::Keyboard::L) {
           // m_isInLineMode = !m_isInLineMode;
            std::cout   << "Line mode toggled. Current mode: " 
                        << (m_isInLineMode ? "Lines (Click and Hold)" : "Cells") 
                        << '\n';
        }*/
    }
    else if (e.type == sf::Event::MouseButtonReleased) {
        m_inputMode->onMouseReleased(e);
    }
    else if (e.type == sf::Event::MouseButtonPressed) {
        m_inputMode->onMousePressed(e);
    }
}

void WireWorld::update()
{
    if (m_isInEditMode) {
        m_inputMode->update();
    }
    else {
        //simulate here
    }
}

const Config & WireWorld::getConfig() const
{
    return *m_pConfig;
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

void WireWorld::setCell(int x, int y, Cell cell)
{
    Cell& c = m_cells[getCellIndex(x, y)];
    c = cell;
    CellularAutomaton::setCellColour(x, y, m_cellColours[(int)c]);
}

WireWorld::Cell WireWorld::getCell(int x, int y)
{
    return m_cells[getCellIndex(x, y)];
}

void WireWorld::onRenderCells(sf::RenderWindow & window)
{
    m_inputMode->render(window);
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
