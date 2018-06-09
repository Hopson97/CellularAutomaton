#include "Application.h"
#include "Util/Config.h"

#include <iostream>

int main()
{
    Config config({1280, 720}, 3);
    config.bgColour = { 150, 150, 150 };
    config.fgColour = { 100, 100, 100 };

    Application app(config);
    app.run();
}
