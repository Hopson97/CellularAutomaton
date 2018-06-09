#include "CellularAutomaton.h"

#include <iostream>
#include "Native/Native.h"

CellularAutomaton::CellularAutomaton(const Config& config)
    :   m_pConfig   (&config)
{
    m_cellVertexPoints.reserve(config.simSize.x * config.simSize.y * 4);
    for (unsigned y = 0; y < config.simSize.y; y++) {
        for (unsigned x = 0; x < config.simSize.x; x++) {
            addQuad(x, y);
        }
    }

    m_pixelBuffer.create(1280, 720, m_pConfig->fgColour);

    m_pixelSurfaceTex.loadFromImage(m_pixelBuffer);
    m_pixelSurface.setSize({ 1280.0f, 720.0f });
    m_pixelSurface.setTexture(&m_pixelSurfaceTex);
}

void CellularAutomaton::render(sf::RenderWindow & window)
{
    //m_pixelSurfaceTex.loadFromImage(m_pixelBuffer);
    //window.draw(m_pixelSurface);
    window.draw(m_cellVertexPoints.data(), m_cellVertexPoints.size(), sf::Quads);
}

void CellularAutomaton::makeScreenshot()
{
    static int imageCount = 0;
    std::cout << "Saving image... Please hold...\n";
    std::string fileName = "Screenshots/Screenshot" + std::to_string(imageCount++) + ".png";

    if (m_pixelBuffer.saveToFile(fileName)) {
        std::cout << TextColour::Green << "Saved, to file " << fileName << "! Be aware, fkuture sessions WILL OVERRIDE these images\n\n" << TextColour::Default;
    }
    else {
        std::cout << TextColour::Red << "Failed to save!\n\n" << TextColour::Default;
    }
}

void CellularAutomaton::setCellColour(int x, int y, sf::Color colour)
{
    auto index = (y * m_pConfig->simSize.x + x) * 4;
    for (int i = 0; i < 4; i++)
    {
        m_cellVertexPoints[index + i].color = colour;
    }
    //m_pixelBuffer.setPixel(x, y, colour);
}

void CellularAutomaton::addQuad(unsigned xIndex, unsigned yIndex)
{
    float cellSize = (float)m_pConfig->cellSize;
    sf::Vertex topLeft;
    sf::Vertex topRight;
    sf::Vertex bottomLeft;
    sf::Vertex bottomRight;

    float pixelX = xIndex * cellSize;
    float pixelY = yIndex * cellSize;

    topLeft     .position = { pixelX,               pixelY };
    topRight    .position = { pixelX + cellSize,    pixelY };
    bottomLeft  .position = { pixelX,               pixelY + cellSize };
    bottomRight .position = { pixelX + cellSize,    pixelY + cellSize };

    topLeft     .color = m_pConfig->fgColour;
    topRight    .color = m_pConfig->fgColour;
    bottomLeft  .color = m_pConfig->fgColour;
    bottomRight .color = m_pConfig->fgColour;

    m_cellVertexPoints.push_back(topLeft);
    m_cellVertexPoints.push_back(bottomLeft);
    m_cellVertexPoints.push_back(bottomRight);
    m_cellVertexPoints.push_back(topRight);
}
