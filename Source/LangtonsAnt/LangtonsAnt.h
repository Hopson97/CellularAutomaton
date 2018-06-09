#pragma once

#include <vector>
#include "../CellularAutomaton.h"
#include "Ant.h"

class LangtonsAnt : public CellularAutomaton
{
    enum Cell
    {
        On,
        Off
    };

    public:
        LangtonsAnt(const Config& config);

        void input() override;
        void update() override;

    private:
        void addAnt();
        void updateAnt(Ant& ant);

        std::vector<Ant> m_ants;

        std::vector<Cell> m_cells;
};