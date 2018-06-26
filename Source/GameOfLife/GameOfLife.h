#pragma once

#include <vector>
#include "../CellularAutomaton.h"


class GameOfLife : public CellularAutomaton
{
    enum Cell
    {
        On,
        Off
    };

    public:
        GameOfLife(const Config& config, const Application& app);

        void update() override;

    private:
        std::vector<Cell> m_cells;
};