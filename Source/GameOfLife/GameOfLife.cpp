#include "GameOfLife.h"
#include <iostream>
#include <random>

GameOfLife::GameOfLife(const Config & config, const Application& app)
    : CellularAutomaton(config, app)
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

void GameOfLife::update()
{
    std::vector<std::pair<sf::Vector2i, Cell>> updates;
    cellForEach([&](unsigned x, unsigned y)
    {
        sf::Vector2i loc(x, y);
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

        int index = getCellIndex(x, y);
        auto cell = m_cells[index];
        switch (cell)
        {
            case Cell::On:
                if (count < 2 || count > 3)
                {
                    updates.emplace_back(loc, Cell::Off);
                }
                break;

            case Cell::Off:
                if (count == 3)
                {
                    updates.emplace_back(loc, Cell::On);
                }
                break;
        } 
    });
    for (auto& update : updates) {
        m_cells[getCellIndex(update.first.x, update.first.y)] = update.second;

        CellularAutomaton::setCellColour(update.first.x, update.first.y, 
            update.second == Cell::On ? sf::Color::Black : m_pConfig->fgColour);
    }
}