#include "CellularAutomaton.h"

#include <iostream>
#include "Native/Native.h"

CellularAutomaton::CellularAutomaton(const Config& config, const Application& app)
	: m_pConfig(&config)
	, m_pApplication(&app)
	, m_cells({ (unsigned)config.windowSize.x, (unsigned)config.windowSize.y }, sf::Color::Black)
	, m_surface({ (float)config.windowSize.x, (float)config.windowSize.y })
{

}

void CellularAutomaton::render(sf::RenderWindow& window)
{
	onRenderCells(window);
	m_texture.loadFromImage(m_cells);
	m_surface.setTexture(&m_texture);
	window.draw(m_surface);

	onRenderGUI(window);



}

void CellularAutomaton::makeScreenshot()
{/*
	static int imageCount = 0;
	std::cout << "Saving image... Please hold...\n";
	std::string fileName = "Screenshots/Screenshot" + std::to_string(imageCount++) + ".png";

	if (m_pixelBuffer.saveToFile(fileName)) {
		std::cout << TextColour::Green << "Saved, to file " << fileName << "! Be aware, fkuture sessions WILL OVERRIDE these images\n\n" << TextColour::Default;
	}
	else {
		std::cout << TextColour::Red << "Failed to save!\n\n" << TextColour::Default;
	}*/
}

unsigned CellularAutomaton::getCellIndex(unsigned x, unsigned y)
{
	return x + y * m_pConfig->simSize.x;
}

void CellularAutomaton::setCellColour(int x, int y, sf::Color colour)
{
	m_cells.setPixel({ (unsigned)x, (unsigned)y }, colour);
	//m_pixelBuffer.setPixel(x, y, colour);
}

