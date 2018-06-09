#pragma once

#include <SFML/Graphics.hpp>
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
        void setCellColour(int x, int y, sf::Color colour);
        const Config* m_pConfig;

    private:
        sf::Vertex m_cells;
        sf::Image           m_pixelBuffer;
        sf::Texture         m_pixelSurfaceTex;
        sf::RectangleShape  m_pixelSurface;
};