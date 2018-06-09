#include "GameOfLife.h"
#include <iostream>
#include <random>

GameOfLife::GameOfLife(const Config & config)
    : CellularAutomaton(config) 
    , m_cells(config.simSize.x * config.simSize.y)
{
    std::mt19937 rng((unsigned)std::time(nullptr));
    cellForEach([&](unsigned x, unsigned y)
    {
        unsigned index = getCellIndex(x, y);
        std::uniform_int_distribution<int> dist(0, 1);

        auto& cell = m_cells[index];
        cell = (Cell)dist(rng);
        CellularAutomaton::setCellColour(x, y, cell == Cell::On ? sf::Color::Black : m_pConfig->fgColour);
    });
}

void GameOfLife::input()
{
}

void GameOfLife::update()
{
    std::vector<Cell> newCells(m_pConfig->simSize.x * m_pConfig->simSize.y);
    cellForEach([&](unsigned x, unsigned y)
    {
        unsigned count = 0;
        for (int nX = -1; nX <= 1; nX++)    //check neighbours
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
                if (cell == Cell::On)
                    count++;
            }

        auto cell = m_cells[getCellIndex(x, y)];
        auto& updateCell = newCells[getCellIndex(x, y)];
        updateCell = cell;
        switch (cell)
        {
            case Cell::On:
                if (count < 2 || count > 3)
                {
                    updateCell = Cell::Off;
                }
                break;

            case Cell::Off:
                if (count == 3)
                {
                    updateCell = Cell::On;
                }
                break;
        }
        CellularAutomaton::setCellColour(x, y, updateCell == Cell::On ? sf::Color::Black : m_pConfig->fgColour);
    });
    m_cells = std::move(newCells);
}