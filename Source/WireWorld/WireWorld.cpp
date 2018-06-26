#include "WireWorld.h"

#include <iostream>
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

    if (e.type == sf::Event::MouseButtonReleased) {
        if (!m_isInLineMode) {
            mouseInput(e);
        }
    }
    else if (e.type == sf::Event::MouseButtonPressed && m_isInLineMode) {
        auto cellLocation = getMouseInputPosition();
        if (!cellLocation) {
            return;
        }
        int cellX = cellLocation->x;
        int cellY = cellLocation->y;
        int cellIndex = getCellIndex(cellX, cellY);
        Cell& cell = m_cells[cellIndex];

        if (!m_isDoingLineInput) {
            m_inputBegin = { cellX, cellY };
            m_isDoingLineInput = true;
        }
        else {
            m_inputEnd = { cellX, cellY };
        }
        
    }
}

void WireWorld::update()
{
}

void WireWorld::onRenderCells(sf::RenderWindow & window)
{
}

void WireWorld::mouseInput(const sf::Event& e)
{
    auto cellLocation = getMouseInputPosition();
    if (!cellLocation) {
        return;
    }
    int cellX = cellLocation->x;
    int cellY = cellLocation->y;
    int cellIndex = getCellIndex(cellX, cellY);
    Cell& cell = m_cells[cellIndex];

    //Input for cell conductors
    if (e.mouseButton.button == sf::Mouse::Left) {
        if (cell == Cell::Conductor || cell == Cell::Empty) {
            cell = m_isInEraseMode ?
                Cell::Empty :
                Cell::Conductor;
        }
    }
    //Input for cell heads
    else if (e.mouseButton.button == sf::Mouse::Right) {
        if (cell == Cell::Conductor || cell == Cell::Head) {
            cell = m_isInEraseMode ?
                Cell::Conductor :
                Cell::Head;
        }
    }
    CellularAutomaton::setCellColour(cellX, cellY, m_cellColours[(int)cell]);
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
