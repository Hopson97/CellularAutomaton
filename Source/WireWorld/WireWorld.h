#pragma once

#include <vector>
#include "../CellularAutomaton.h"

class WireWorld : public CellularAutomaton
{
    enum class Cell
    {
        Empty,
        Head,
        Tail,
        Conductor
    };
public:
    WireWorld(const Config& config);

    void input(const sf::Event& e) override;
    void update() override;

private:
    std::vector<Cell> m_cells;
};