#pragma once

#include "Colony.h"
#include <vector>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Image.hpp>
#include "../Util/Config.h"

std::vector<Colony> createColonyStats();
std::vector<sf::Vector2f> createColonyStartLocations(const sf::Image& bg, const Config& config);