#pragma once

#include <vector>
#include "../CellularAutomaton.h"
#include "Creature.h"

class PredatorAndPrey : public CellularAutomaton
{
    enum Cell
    {
        On,
        Off
    };

    public:
        PredatorAndPrey(const Config& config);

        void update() override;

    private:
        void updatePredator(Creature& thisCreature, Creature& otherCreature);
        void updatePrey(Creature& thisCreature, Creature& otherCreature);

        std::vector<Creature> m_creatures;

        std::vector<Cell> m_cells;
        int m_preyCount = 0;
        int m_predatorCount = 0;
};