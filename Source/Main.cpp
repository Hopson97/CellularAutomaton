#include "Application.h"
#include "Util/Config.h"

#include "LangtonsAnt/LangtonsAnt.h"
#include "GameOfLife/GameOfLife.h"
#include "PredatorAndPrey/PredatorAndPrey.h"
#include "BriansBrain/BriansBrain.h"
#include "WireWorld/WireWorld.h"

#include <iostream>
#include <any>
#include <vector>
#include "Native/Native.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace 
{
    void setConsolePosition()
    {
#ifdef _WIN32
        HWND consoleWindow = GetConsoleWindow();
        SetWindowPos(consoleWindow, 0, 0, 0, 500, 500, SWP_NOSIZE | SWP_NOZORDER);
#endif
    }

    constexpr int NUM_OPTIONS = 6;
    Config config({ 1280, 720 }, 8);

    template<typename T>
    void run()
    {
        std::cout << "\nTo choose another Cellular Automaton, simply close the window\n";
        std::cout << TextColour::Green << "Controls: \n" << TextColour::Default;
        std::cout << "Up - Zoom in\nDown - Zoom out\nWASD - Move Around\n";
        std::cout << "R - Reset the view\n";
        std::cin.ignore();
        Application app(config);
        app.init<T>();
        app.run();
        std::cout << '\n';
    }

    bool isValidChoice(int option)
    {
        return option > 0 && option <= NUM_OPTIONS;
    }
}

int main()
{
    setConsolePosition();
    config.bgColour = { 150, 150, 150 };
    config.fgColour = { 25, 25, 25 };

    bool exit = false;
    while (!exit) {
        int option = 0;
        std::cout << "Which Cellular Automaton would you like to see?\n"
            << "1. Langton's Ant\n"
            << "2. Conway's Game of Life\n"
            << "3. Predator and Prey\n"
            << "4. Brian's Brain\n"
            << "5. Wire World\n"
            << NUM_OPTIONS << ". Exit\n";
        while (!isValidChoice(option)) {
            std::cin >> option;

            if (!isValidChoice(option)) {
                std::cout << "Invalid option, please pick a number between 1 and " << NUM_OPTIONS << "\n";
                std::cin.ignore();
            }
        }

        switch (option)
        {
            case 1:
                run<LangtonsAnt>();
                break;

            case 2:
                run<GameOfLife>();
                break;

            case 3:
                run<PredatorAndPrey>();
                break;

            case 4:
                run<BriansBrain>();
                break;

            case 5:
                run<WireWorld>();
                break;

            case NUM_OPTIONS:
                exit = true;
                break;

            default:
                break;
        }
    }
}
