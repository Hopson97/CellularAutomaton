#include "WireWorld.h"

WireWorld::WireWorld(const Config & config)
    : CellularAutomaton(config)
    , m_cells(1280 * 720)
{
}

void WireWorld::input(const sf::Event & e)
{
}

void WireWorld::update()
{
}
