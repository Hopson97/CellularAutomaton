#include "Empire.h"
#include <iostream>
#include <random>

Empire::Empire(const Config& config, const Application& app)
    : CellularAutomaton(config, app)
    , m_pConfig (&config)
{
    float x = static_cast<float>(m_pConfig->windowSize.x);
    float y = static_cast<float>(m_pConfig->windowSize.y);


    m_backgroundImg.loadFromFile("res/Empire/world.png");
    m_backgroundTexture.loadFromImage(m_backgroundImg);
    m_backgroundRect.setSize({x, y});
    m_backgroundRect.setTexture(&m_backgroundTexture);



    std::mt19937 rng((unsigned)std::time(nullptr));
}

void Empire::update()
{
    cellForEach([&](unsigned x, unsigned y)
    {
        
    });
}

void Empire::onRenderCells(sf::RenderWindow& window) {

}