#include "Application.h"

#include <iostream>
#include <ctime>
#include <thread>

#include "Util/Random.h"
#include "Util/Config.h"
#include "Native/Native.h"

#include "ResourceManager/ResourceHolder.h"

namespace
{
    sf::Color bgColour = {200, 200, 200};
    sf::Color clrColur = {125, 125, 125};
}

Application::Application(int antCount, const Config& config)
:   m_cells     (config.width * config.height)
,   m_window    ({config.width, config.height}, "Langton's Ant")
,   m_pConfig   (&config)
{
    for (int i = 0; i < antCount; i++)
    {
        addAnt();
    }

    std::fill(m_cells.begin(), m_cells.end(), Cell::Off);

    m_view.setCenter({(float)config.width / 2, (float)config.height / 2});
    m_view.setSize  ({(float)config.width,     (float)config.height});

    m_pixelBuffer.create(m_pConfig->width, m_pConfig->height, bgColour);


    m_pixelSurfaceTex.loadFromImage(m_pixelBuffer);
    m_pixelSurface.setSize({(float)config.width, (float)config.height});
    m_pixelSurface.setTexture(&m_pixelSurfaceTex);

    m_guiText.setFont(ResourceHolder::get().fonts.get("arial"));
    m_guiText.move(10, 3);
    m_guiText.setCharacterSize (18);
    m_guiText.setOutlineColor  (sf::Color::Black);
    m_guiText.setOutlineThickness(2);
}

void Application::run()
{
    sf::Clock deltaClock;
    unsigned year = 0;
    while (m_window.isOpen())
    {
        m_guiText.setString("Generation: " + std::to_string(year++));
        m_fpsCounter.update();

        input (deltaClock.restart().asSeconds());

        for (auto& ant : m_ants)
            update (ant);

        m_pixelSurfaceTex.loadFromImage(m_pixelBuffer);
        render  ();
        pollEvents();
    }
}

void Application::addAnt()
{
    int x = Random::get().intInRange(0, m_pConfig->width - 1);
    int y = Random::get().intInRange(0, m_pConfig->height - 1);
    m_ants.emplace_back(x, y);
}


void Application::pollEvents()
{
    sf::Event e;
    while (m_window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
        {
            m_window.close();
        }
        else if (e.type == sf::Event::KeyPressed)
        {
            if (e.key.code == sf::Keyboard::P)
            {
                std::thread(&Application::makeImage, this).detach();
            }
            else if (e.key.code == sf::Keyboard::Up)
            {
                m_view.zoom(0.99f);
            }
            else if (e.key.code == sf::Keyboard::Down)
            {
                m_view.zoom(1.01f);
            }
            else if (e.key.code == sf::Keyboard::Q)
            {
                addAnt();
            }
        }
    }
}

//Takes the pixels that makes up the people, and save it to an image
void Application::makeImage()
{
    static int imageCount = 0;
    std::cout << "Saving image... Please hold...\n";
    std::string fileName = "Screenshots/Screenshot" + std::to_string(imageCount++) + ".png";

    if (m_pixelBuffer.saveToFile(fileName))
    {
        std::cout << TextColour::Green << "Saved, to file " << fileName << "! Be aware, future sessions WILL OVERRIDE these images\n\n" << TextColour::Default;
    }
    else
    {
        std::cout << TextColour::Red << "Failed to save!\n\n" << TextColour::Default;
    }
}

void Application::input(float dt)
{
    float speed = 100;
    sf::Vector2f change;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        change.y -= speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        change.y += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        change.x -= speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        change.x += speed;
    }

    m_view.move(change * dt);
}

void Application::update(Ant& ant)
{
    ant.translate();
    const auto& position    = ant.getPosition();

    //handle oob/ wrapping
    if (position.x == (int)m_pConfig->width)
        ant.setX(0);
    else if (position.x == -1)
        ant.setX(m_pConfig->width - 1);

    if (position.y == (int)m_pConfig->height)
        ant.setY(0);
    else if (position.y == -1)
        ant.setY(m_pConfig->height - 1);

    auto& cell = m_cells[position.y * m_pConfig->width + position.x];

    sf::Color colour;
    switch(cell)
    {
        case Cell::Off:
            cell = Cell::On;
            ant.turn(Turn::Right);
            colour = ant.getColour();
            break;

        case Cell::On:
            cell = Cell::Off;
            ant.turn(Turn::Left);
            colour = bgColour;
            break;
    }
    m_pixelBuffer.setPixel(ant.getPosition().x,
                           ant.getPosition().y,
                           colour);
}

void Application::render()
{
    m_window.clear(clrColur);

    //Pixels
    m_window.setView(m_view);
    m_window.draw(m_pixelSurface);

    //GUI
    m_window.setView(m_window.getDefaultView());
    m_window.draw(m_guiText);
    m_fpsCounter.draw(m_window);

    m_window.display();
}

