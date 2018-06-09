#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

#include "Util/FPSCounter.h"
#include "Ant.h"

struct Config;

class Application
{
    enum Cell
    {
        On,
        Off
    };

    public:
        Application(int antCount, const Config& config);

        void run();

    private:
        void addAnt();

        void makeImage();

        void pollEvents();
        void input  (float dt);
        void update (Ant& ant);
        void render ();

        void testOutOfBounds(sf::Vector2i& position);

        std::vector<Ant> m_ants;

        std::vector<Cell> m_cells;

        sf::RenderWindow m_window;

        FPSCounter m_fpsCounter;

        sf::Image           m_pixelBuffer;
        sf::Texture         m_pixelSurfaceTex;
        sf::RectangleShape  m_pixelSurface;
        sf::Text            m_guiText;
        sf::View            m_view;

        const Config* m_pConfig = nullptr;
};

#endif // APPLICATION_H_INCLUDED
