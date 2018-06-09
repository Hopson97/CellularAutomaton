#include "PredatorAndPrey.h"

#include "../Util/Random.h"

PredatorAndPrey::PredatorAndPrey(const Config & config)
    :   CellularAutomaton(config)
    , m_creatures(config.simSize.x * config.simSize.y)
{
    cellForEach([&](unsigned x, unsigned y)
    {
        auto index = getCellIndex(x, y);
        auto type = m_creatures[index].getType();
        switch (type)
        {
        case CreatureType::Prey:
            m_preyCount++;
            break;

        case CreatureType::Predator:
            m_predatorCount++;
            break;

        case CreatureType::Nothing:
            break;
        }
        setCellColour(x, y, m_creatures[index].getColour());
    });

}

void PredatorAndPrey::update()
{
    cellForEach([&](unsigned x, unsigned y)
    {
        auto index = getCellIndex(x, y);
        auto& thisCreature = m_creatures[index];
        auto thisType = thisCreature.getType();

        if (thisType == CreatureType::Nothing)
            return;

        int xChange = Random::get().intInRange(-1, 1);
        int yChange = Random::get().intInRange(-1, 1);
        int xAdj = x + xChange;
        int yAdj = y + yChange;

        if (xAdj < 0 || xAdj >= (int)m_pConfig->simSize.x) return;
        if (yAdj < 0 || yAdj >= (int)m_pConfig->simSize.y) return;

        auto adjIndex = getCellIndex(xAdj, yAdj);
        auto& otherCreature = m_creatures[adjIndex];

        thisCreature.update();
        switch (thisType)
        {
            case CreatureType::Predator:
                updatePredator(thisCreature, otherCreature);
                break;

            case CreatureType::Prey:
                updatePrey(thisCreature, otherCreature);
                break;

            default:
                break;
        }

        setCellColour(x, y, m_creatures[index].getColour());
    });
}

void PredatorAndPrey::updatePredator(Creature & thisCreature, Creature & otherCreature)
{
    if (thisCreature.getHealth() <= 0)
    {
        m_predatorCount--;
        thisCreature.setType(CreatureType::Nothing);
        return;
    }

    auto otherType = otherCreature.getType();

    switch (otherType)
    {
    case CreatureType::Prey:
        m_preyCount--;
        m_predatorCount++;
        otherCreature.setType(CreatureType::Predator);
        thisCreature.heal(otherCreature.getHealth());
        break;

    case CreatureType::Predator:
        break;

    case CreatureType::Nothing:
        thisCreature.move(otherCreature);
        break;
    }
}

void PredatorAndPrey::updatePrey(Creature & thisCreature, Creature & otherCreature)
{
    auto otherType = otherCreature.getType();

    bool reproduce = false;
    if (thisCreature.getHealth() >= Creature::MAX_HEALTH)
    {
        thisCreature.setHealth(10);
        reproduce = true;
    }

    switch (otherType)
    {
    case CreatureType::Prey:
        break;

    case CreatureType::Predator:
        break;

    case CreatureType::Nothing:
        if (reproduce)
        {
            m_preyCount++;
            thisCreature.reproduce(otherCreature);
        }
        else
        {
            thisCreature.move(otherCreature);
        }
        break;

    }
}
