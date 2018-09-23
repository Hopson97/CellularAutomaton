#include "Empire.h"
#include <iostream>
#include <random>

Empire::Empire(const Config& config, const Application& app)
    : CellularAutomaton(config, app)
    , m_pConfig (&config)
{
    m_background.loadFromFile("res/Empire/world.png");
    std::mt19937 rng((unsigned)std::time(nullptr));
}

void Empire::update()
{
    cellForEach([&](unsigned x, unsigned y)
    {
        
    });
}