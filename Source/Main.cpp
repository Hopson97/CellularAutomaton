#include "Application.h"
#include "Util/Config.h"

#include "LangtonsAnt/LangtonsAnt.h"
#include "GameOfLife/GameOfLife.h"
#include "PredatorAndPrey/PredatorAndPrey.h"
#include "BriansBrain/BriansBrain.h"

#include <iostream>
#include "Native/Native.h"
constexpr int NUM_OPTIONS = 5;


void run(const Config& config, std::unique_ptr<CellularAutomaton> cellularAutomaton)
{
    std::cout << "\nTo choose another Cellular Automaton, simply close the window\n";
    std::cout << TextColour::Green << "Controls: \n" << TextColour::Default;
    std::cout << "Up - Zoom in\nDown - Zoom out\nWASD - Move Around\n\n";
    std::cin.ignore();
    Application app(config, std::move(cellularAutomaton));
    app.run();
}

bool isValidChoice(int option)
{
    return option > 0 && option <= NUM_OPTIONS;
}

int main()
{
    Config config({1280, 720}, 3);
    config.bgColour = { 150, 150, 150 };
    config.fgColour = { 50, 50, 50 };

    bool exit = false;
    while (!exit) {
        int option = 0;
        std::cout << "Which Cellular Automaton would you like to see?\n"
            << "1. Langton's Ant\n"
            << "2. Conway's Game of Life\n"
            << "3. Predator and Prey\n"
            << "4. Brian's Brain\n"
            << NUM_OPTIONS << ". Exit\n";
        while (!isValidChoice(option)) {
            std::cin >> option;

            if (!isValidChoice(option)) {
                std::cout << "Invalid option, please pick a number between 1 and " << NUM_OPTIONS << "\n";
            }
        }

        switch (option)
        {
            case 1:
                run(config, std::make_unique<LangtonsAnt>(config));
                break;

            case 2:
                run(config, std::make_unique<GameOfLife>(config));
                break;

            case 3:
                run(config, std::make_unique<PredatorAndPrey>(config));
                break;

            case 4:
                run(config, std::make_unique<BriansBrain>(config));
                break;

            case NUM_OPTIONS:
                exit = true;
                break;

            default:
                break;
        }
    }
}
