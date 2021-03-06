#pragma once

#include <vector>
#include "Colony.h"
#include "../CellularAutomaton.h"


class Empire : public CellularAutomaton
{
    public:
        Empire(const Config& config, const Application& app);

        void update() override;

        void onRenderCells(sf::RenderWindow& window) override;

    private:
        void setUpColonies();

        /* 
            Cells
        */
        std::vector<Colony> m_colonies;

        /* 
            Background
        */
        const Config* m_pConfig;
        sf::Image m_backgroundImg;
        sf::Texture m_backgroundTexture;
        sf::RectangleShape m_backgroundRect;
        //std::vector<Cell> m_cells;
};