#pragma once

#include "../CellularAutomaton.h"

class BriansBrain : public CellularAutomaton
{
    enum class Cell : uint8_t
    {
        Off,
        On,
        Dying
    };

    public:
        BriansBrain(const Config& config);

        void update() override;

    private:
        void wrapVector(int& x, int& y);

        sf::Color getCellColour(Cell cell);

        std::vector<Cell> m_cells;
};