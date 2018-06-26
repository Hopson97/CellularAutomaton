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

        void input(const sf::Event& e) override;
        void update() override;

    private:
        sf::Vector2i addAnt();
        void updateAnt(Ant& ant);

        std::vector<Ant> m_ants;
        std::vector<Cell> m_cells;
};