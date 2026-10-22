#include "Application.h"

#include <iostream>
#include <ctime>
#include <thread>

#include "Util/Random.h"
#include "Util/Config.h"
#include "Native/Native.h"

#include "ResourceManager/ResourceHolder.h"

Application::Application(const Config& config)
	: m_window(sf::VideoMode{ {config.windowSize.x, config.windowSize.y} }, "Cellular Automaton")
	, m_pConfig(&config)
	, m_guiText(ResourceHolder::get().fonts.get("arial"))
{
	resetView();

	m_guiText.move({ 10, 3 });
	m_guiText.setCharacterSize(18);
	m_guiText.setOutlineColor(sf::Color::Black);
	m_guiText.setOutlineThickness(2);

	m_window.setFramerateLimit(config.fps);
}

void Application::run()
{
	sf::Clock deltaClock;
	unsigned year = 0;
	m_window.setKeyRepeatEnabled(false);
	while (m_window.isOpen()) {
		m_guiText.setString("Generation: " + std::to_string(year++));
		m_fpsCounter.update();

		input(deltaClock.restart().asSeconds());
		m_automaton->update();

		render();
		pollEvents();
	}
}

const sf::RenderWindow& Application::getWindow() const
{
	return m_window;
}

void Application::pollEvents()
{
	float zoomFactor = 0.2f;
	while (auto e = m_window.pollEvent())
	{
		m_automaton->input(*e);
		m_keyboard.update(*e);

		if (e->is<sf::Event::Closed>())
		{
			m_window.close();
		}
		if (auto wheel = e->getIf<sf::Event::MouseWheelScrolled>())
		{
			auto mousePixel = wheel->position;

			auto before = m_window.mapPixelToCoords(mousePixel, m_view);
			if (wheel->delta > 0) {
				m_view.zoom(1.f - zoomFactor);
			}
			else if (wheel->delta < 0) {
				m_view.zoom(1.f + zoomFactor);
			}

			auto after = m_window.mapPixelToCoords(mousePixel, m_view);
			m_view.move(before - after);
		}
	}
}

void Application::input(float dt)
{
	constexpr float zoomSpeed = 0.5f;
	float speed = 250;
	sf::Vector2f change;
	if (m_keyboard.isKeyDown(sf::Keyboard::Key::W)) {
		change.y -= speed;
	}
	else if (m_keyboard.isKeyDown(sf::Keyboard::Key::S))
	{
		change.y += speed;
	}
	if (m_keyboard.isKeyDown(sf::Keyboard::Key::A))
	{
		change.x -= speed;
	}
	else if (m_keyboard.isKeyDown(sf::Keyboard::Key::D))
	{
		change.x += speed;
	}

	if (m_keyboard.isKeyDown(sf::Keyboard::Key::P))
	{
		//std::thread(&Application::makeImage, this).detach();
	}
	if (m_keyboard.isKeyDown(sf::Keyboard::Key::Up))
	{
		m_view.zoom(std::exp(-zoomSpeed * dt));
	}
	if (m_keyboard.isKeyDown(sf::Keyboard::Key::Down))
	{
		m_view.zoom(std::exp(zoomSpeed * dt));
	}
	if (m_keyboard.isKeyDown(sf::Keyboard::Key::R))
	{
		resetView();
	}

	m_view.move(change * dt);
}

void Application::render()
{
	m_window.setView(m_view);
	m_window.clear(m_pConfig->bgColour);

	//Pixels
	m_window.setView(m_view);
	m_automaton->render(m_window);

	//GUI
	m_window.setView(m_window.getDefaultView());
	m_window.draw(m_guiText);
	m_fpsCounter.draw(m_window);

	m_window.display();
}

void Application::resetView()
{
	m_view = sf::View();
	m_view.setCenter({ (float)m_pConfig->windowSize.x / 2,  (float)m_pConfig->windowSize.y / 2 });
	m_view.setSize({ (float)m_pConfig->windowSize.x,        (float)m_pConfig->windowSize.y });
}

