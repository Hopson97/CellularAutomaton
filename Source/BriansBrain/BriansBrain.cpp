#include "BriansBrain.h"

#include <random>

BriansBrain::BriansBrain(const Config & config, const Application& app)
    : CellularAutomaton(config, app)
    , m_cells(config.simSize.x * config.simSize.y)
{ 
    std::mt19937 rng((unsigned)std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, 1);
    CellularAutomaton::cellForEach([&](unsigned x, unsigned y) 
    {
        auto& cell = m_cells[getCellIndex(x, y)];
        cell = (Cell)dist(rng);
        CellularAutomaton::setCellColour(x, y, getCellColour(cell));
    });
}

void BriansBrain::update()
{
    std::vector<Cell> newCells(m_pConfig->simSize.x * m_pConfig->simSize.y);
    CellularAutomaton::cellForEach([&](unsigned x, unsigned y)
    {
        auto& cell = m_cells[getCellIndex(x, y)];
        auto& newCell = newCells[getCellIndex(x, y)];
        switch (cell)
        {
            case BriansBrain::Cell::Off: {
                int cellCount = 0;
                for (int yOffset = -1; yOffset <= 1; yOffset++) {
                    for (int xOffset = -1; xOffset <= 1; xOffset++) {
                        int newX = x + xOffset;
                        int newY = y + yOffset;
                        wrapVector(newX, newY);
                        int newIndex = getCellIndex(newX, newY);
                        if (m_cells[newIndex] == Cell::On) {
                            cellCount++;
                        }
                    }
                }
                if (cellCount == 2) {
                    newCell = Cell::On;
                    CellularAutomaton::setCellColour(x, y, getCellColour(newCell));
                }}
                return;
            case BriansBrain::Cell::On:
                newCell = Cell::Dying;
                CellularAutomaton::setCellColour(x, y, getCellColour(newCell));
                return;
            case BriansBrain::Cell::Dying:
                newCell = Cell::Off;
                CellularAutomaton::setCellColour(x, y, getCellColour(newCell));
                return;
        }
        newCell = cell;
    });
    m_cells = std::move(newCells);
}


void BriansBrain::wrapVector(int & x, int & y)
{
    if (x > (int)m_pConfig->simSize.x - 1) {
        x = 0;
    } 
    else if (x < 0) {
        x = m_pConfig->simSize.x - 1;
    }
    if (y > (int)m_pConfig->simSize.y - 1) {
        y = 0;
    }
    else if (y < 0) {
        y = m_pConfig->simSize.y - 1;
    }
}

sf::Color BriansBrain::getCellColour(Cell cell)
{
    switch (cell)
    {
        case BriansBrain::Cell::Off:
            return m_pConfig->fgColour;
        case BriansBrain::Cell::On:
            return sf::Color::Blue;
        case BriansBrain::Cell::Dying:
            return sf::Color::White;
    }
    //to make compilers happy
    return sf::Color::Red;
}
