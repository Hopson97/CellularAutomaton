#include "Application.h"
#include "Util/Config.h"

#include "LangtonsAnt/LangtonsAnt.h"
#include "GameOfLife/GameOfLife.h"
#include "PredatorAndPrey/PredatorAndPrey.h"
#include "BriansBrain/BriansBrain.h"

#include <iostream>
#include "Native/Native.h"
constexpr int NUM_OPTIONS = 6;


template<typename T>
void run(const Config& config)
{
    std::cout << "\nTo choose another Cellular Automaton, simply close the window\n";
    std::cout << TextColour::Green << "Controls: \n" << TextColour::Default;
    std::cout << "Up - Zoom in\nDown - Zoom out\nWASD - Move Around\n\n";
    std::cin.ignore();
    Application app(config, std::make_unique<T>(config));
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
            << "5. Wire World"
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
                run<LangtonsAnt>(config);
                break;

            case 2:
                run<GameOfLife>(config);
                break;

            case 3:
                run<PredatorAndPrey>(config);
                break;

            case 4:
                run<BriansBrain>(config);
                break;

            case 5:
                break;

            case NUM_OPTIONS:
                exit = true;
                break;

            default:
                break;
        }
    }
}
