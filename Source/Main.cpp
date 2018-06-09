#include "Application.h"
#include "Util/Config.h"

#include <iostream>

int main()
{
    Config config;
    config.width    = 1280;
    config.height   = 720;

    std::string inputBuffer;
    std::cout << "\nHow many ants? [Enter a positive numbers] ";
    std::cin >> inputBuffer;

    for (auto c : inputBuffer)
    {
        if (!isdigit(c))
        {
            std::cout << "Invalid input, must be a number greater than 0\n";
            main(); //hacky af but it works
        }
    }
    int n = std::stoi(inputBuffer);
    if (n == 0)
    {
        std::cout << "Invalid input, must be a number greater than 0\n";
        main(); //hacky af but it works
    }

    std::cout << "Press Q to add more ants!\n";

    Application app(config);
    app.run();
}
