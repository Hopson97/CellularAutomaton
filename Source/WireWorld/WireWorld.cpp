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

    std::cout << "P - Switch to POINT input mode\n";
    std::cout << "L - Switch to LINE input mode\n";
    std::cout << "E - Toggle ERASE mode\n";
    std::cout << "Q - Toggle simulation/ Edit mode\n";

    std::cout << "Current mode: Editing, LINE mode \n";
}

void WireWorld::input(const sf::Event& e)
{
    if (e.type == sf::Event::KeyReleased) {
        m_inputMode->onKeyPressed(e.key.code);
        
        if (e.key.code == sf::Keyboard::P) {
            std::cout << "Switched to POINT input mode" << '\n';
            m_inputMode = std::make_unique<PointInputMode>(*this);
        }
        else if (e.key.code == sf::Keyboard::L) {
            std::cout << "Switched to LINE input mode" << '\n';
            m_inputMode = std::make_unique<LineInputMode>(*this);
        }
        else if (e.key.code == sf::Keyboard::Q) {
            std::cout << "Toggled SIM/EDIT mode" << '\n';
            m_isInEditMode = !m_isInEditMode;
        }
    }

    auto cellLocation = getMouseInputPosition();
    if (!cellLocation) {
        return;
    }
    auto cellInfo = getCellPointInfo(*cellLocation);

    if (e.type == sf::Event::MouseButtonReleased) {
        m_inputMode->onMouseReleased(e, cellInfo);
    }
    else if (e.type == sf::Event::MouseButtonPressed) {
        m_inputMode->onMousePressed(e, cellInfo);
    }
}

void WireWorld::update()
{
    if (m_isInEditMode) {
        auto cellLocation = getMouseInputPosition();
        if (!cellLocation) {
            return;
        }
        auto cellInfo = getCellPointInfo(*cellLocation);
        m_inputMode->update(cellInfo);
    }
    else {
        std::vector<std::pair<sf::Vector2i, Cell>> updates;

        CellularAutomaton::cellForEach([&](unsigned x, unsigned y) {
            auto& cell = m_cells[getCellIndex(x, y)];
            sf::Vector2i coord(x, y);
            std::pair<sf::Vector2i, Cell> thisUpdate = { coord, cell };
            switch (cell)
            {
                case Cell::Tail:
                    thisUpdate = updates.emplace_back(coord, Cell::Conductor);
                    break;

                case Cell::Head:
                    thisUpdate = updates.emplace_back(coord, Cell::Tail);
                    break;

                case Cell::Conductor: {
                    int count = 0;
                    for (int nX = -1; nX <= 1; nX++) {
                        for (int nY = -1; nY <= 1; nY++)
                        {
                            int newX = nX + x;
                            int newY = nY + y;

                            if (newX == -1 || newX == (int)m_pConfig->simSize.x ||
                                newY == -1 || newY == (int)m_pConfig->simSize.y || //out of bounds
                                (nX == 0 && nY == 0)) //Cell itself
                            {
                                continue;
                            }

                            auto cell = m_cells[getCellIndex(newX, newY)];
                            if (cell == Cell::Head)
                                count++;
                        }
                    }
                    if (count > 0) { std::cout << count << std::endl; }
                    if (count == 1 || count == 2) {
                        thisUpdate = updates.emplace_back(coord, Cell::Head);
                    }
                    break; }

                default:
                    break;
            }
            CellularAutomaton::setCellColour(x, y, m_cellColours[(int)thisUpdate.second]);
        });

        for (auto& update : updates) {
            setCell(update.first.x, update.first.y, update.second);
        }
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
