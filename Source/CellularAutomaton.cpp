#include "CellularAutomaton.h"

#include <iostream>
#include "Native/Native.h"

CellularAutomaton::CellularAutomaton(const Config& config)
    :   m_pConfig   (&config)
{
    m_pixelBuffer.create(1280, 720, { 100, 100, 100 });

    m_pixelSurfaceTex.loadFromImage(m_pixelBuffer);
    m_pixelSurface.setSize({ 1280.0f, 720.0f });
    m_pixelSurface.setTexture(&m_pixelSurfaceTex);
}

void CellularAutomaton::render(sf::RenderWindow & window)
{
    m_pixelSurfaceTex.loadFromImage(m_pixelBuffer);
    window.draw(m_pixelSurface);
}

void CellularAutomaton::makeScreenshot()
{
    static int imageCount = 0;
    std::cout << "Saving image... Please hold...\n";
    std::string fileName = "Screenshots/Screenshot" + std::to_string(imageCount++) + ".png";

    if (m_pixelBuffer.saveToFile(fileName))
    {
        std::cout << TextColour::Green << "Saved, to file " << fileName << "! Be aware, future sessions WILL OVERRIDE these images\n\n" << TextColour::Default;
    }
    else
    {
        std::cout << TextColour::Red << "Failed to save!\n\n" << TextColour::Default;
    }
}

void CellularAutomaton::setCellColour(int x, int y, sf::Color colour)
{
    m_pixelBuffer.setPixel(x, y, colour);
}
