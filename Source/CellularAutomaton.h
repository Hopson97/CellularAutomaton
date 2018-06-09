#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Util/Config.h"

class CellularAutomaton
{
    public:
        CellularAutomaton(const Config& config);

        virtual void input() {}
        virtual void update() = 0;
        void render(sf::RenderWindow& window);

        void makeScreenshot();
    
    protected:
        unsigned getCellIndex(unsigned x, unsigned y);
        void setCellColour(int x, int y, sf::Color colour);
        const Config* m_pConfig;

    private:
        void addQuad(unsigned xIndex, unsigned yIndex);
        std::vector<sf::Vertex> m_cellVertexPoints;
};