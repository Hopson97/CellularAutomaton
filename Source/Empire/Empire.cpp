#include "Empire.h"
#include <iostream>
#include <random>

#include "ColonyGenerator.h"

Empire::Empire(const Config& config, const Application& app)
    : CellularAutomaton(config, app)
    , m_pConfig (&config)
{
    float x = static_cast<float>(m_pConfig->windowSize.x);
    float y = static_cast<float>(m_pConfig->windowSize.y);


    m_backgroundImg.loadFromFile("Res/Empire/world.png");
    m_backgroundTexture.loadFromImage(m_backgroundImg);
    m_backgroundRect.setSize({x, y});
    m_backgroundRect.setTexture(&m_backgroundTexture);

    cellForEach([&](unsigned x, unsigned y)
    {
        CellularAutomaton::setCellColour(x, y, {0, 0, 0, 0});
    });



    std::mt19937 rng((unsigned)std::time(nullptr));
}

void Empire::update()
{
    cellForEach([&](unsigned x, unsigned y)
    {
        
    });
}

void Empire::onRenderCells(sf::RenderWindow& window) {
    window.draw(m_backgroundRect);
}

void Empire::setUpColonies() {
    m_colonies          = createColonyStats();
    auto startLocations = createColonyStartLocations(m_backgroundImg, *m_pConfig);

    for (unsigned i = 1; i < m_colonies.size(); i++) {
        auto& colony = m_colonies[i];
        auto& start  = startLocations[i];

        //Place upto 50 people
        for (int j = 0; j < 50; j++) {
            
        }
    }
}