#pragma once

#include <vector>
#include "../CellularAutomaton.h"


class Empire : public CellularAutomaton
{
    public:
        Empire(const Config& config, const Application& app);

        void update() override;

    private:
        const Config* m_pConfig;
        sf::Image m_background;
        //std::vector<Cell> m_cells;
};