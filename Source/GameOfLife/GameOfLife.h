#pragma once

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
    GameOfLife(const Config& config);

    void input() override;
    void update() override;

private:
    unsigned getCellIndex(unsigned x, unsigned y);

    template<typename F>
    void cellForEach(const Config& config, F f)
    {
        for (unsigned y = 0; y < config.height; y++) {
            for (unsigned x = 0; x < config.width; x++) {
                f(x, y);
            }
        }
    }

    std::vector<Cell> m_cells;
};