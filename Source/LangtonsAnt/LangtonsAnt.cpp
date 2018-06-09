#include "LangtonsAnt.h"

#include "../Util/Random.h"
#include "../Util/Config.h"

LangtonsAnt::LangtonsAnt(const Config& config)
    : CellularAutomaton(config)
    , m_cells(1280 * 720)
{
    for (int i = 0; i < 5; i++) {
        addAnt();
    }
}

void LangtonsAnt::input()
{
}

void LangtonsAnt::update()
{
    for (auto& ant : m_ants)
        updateAnt(ant);
}

void LangtonsAnt::updateAnt(Ant& ant)
{
    ant.translate();
    const auto& position = ant.getPosition();

    //handle oob/ wrapping
    if (position.x == 1280)
        ant.setX(0);
    else if (position.x == -1)
        ant.setX(m_pConfig->simSize.x - 1);

    if (position.y == (int)m_pConfig->simSize.y)
        ant.setY(0);
    else if (position.y == -1)
        ant.setY(m_pConfig->simSize.y - 1);

    auto& cell = m_cells[position.y * m_pConfig->simSize.x + position.x];

    sf::Color colour;
    switch (cell) {
    case Cell::Off:
        cell = Cell::On;
        ant.turn(Turn::Right);
        colour = ant.getColour();
        break;

    case Cell::On:
        cell = Cell::Off;
        ant.turn(Turn::Left);
        colour = m_pConfig->fgColour;
        break;
    }

    CellularAutomaton::setCellColour(ant.getPosition().x,
        ant.getPosition().y,
        colour);
}

void LangtonsAnt::addAnt()
{
    int x = Random::get().intInRange(0, m_pConfig->simSize.x - 1);
    int y = Random::get().intInRange(0, m_pConfig->simSize.y - 1);
    m_ants.emplace_back(x, y);
}
