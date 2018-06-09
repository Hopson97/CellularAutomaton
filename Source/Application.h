#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <memory>
#include <SFML/Graphics.hpp>

#include "Util/FPSCounter.h"

#include "CellularAutomaton.h"

struct Config;

class Application
{
    public:
        Application(const Config& config);

        void run();

    private:
        void pollEvents();
        void input  (float dt);
        void render ();

        std::unique_ptr<CellularAutomaton> m_automaton;

        sf::RenderWindow m_window;
        FPSCounter m_fpsCounter;

        sf::Text            m_guiText;
        sf::View            m_view;

        const Config* m_pConfig = nullptr;
};

#endif // APPLICATION_H_INCLUDED
