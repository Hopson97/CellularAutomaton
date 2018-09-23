#include "ColonyGenerator.h"

#include <random>

namespace 
{
    constexpr unsigned COLONY_COUNT = 10;
}
std::vector<Colony> createColonyStats()
{
    std::vector<Colony> cols;
    std::mt19937 rng((unsigned)std::time(nullptr));
    std::uniform_int_distribution<unsigned> minStr(10, 20);
    std::uniform_int_distribution<unsigned> maxStr(10, 20);
    std::uniform_int_distribution<uint8_t> colours(0, 255);

    //Create colony stats
    for (int i = 0; i < COLONY_COUNT; i++) {
        Colony c;
        c.id = i;
        c.minStrStart = minStr(rng);
        c.maxStrStart = maxStr(rng);
        c.colour = {
            colours(rng), colours(rng), colours(rng)
        };
        cols.push_back(c);
    }
    return cols;
}

std::vector<sf::Vector2f> createColonyStartLocations(const sf::Image& bg, const Config& config)
{
    std::vector<sf::Vector2f> locations;
    std::mt19937 rng((unsigned)std::time(nullptr));
    std::uniform_int_distribution<unsigned> w(0, bg.getSize.x() - 1);
    std::uniform_int_distribution<unsigned> h(0, bg.getSize.y() - 1);

    //Create colony stats
    for (int i = 0; i < COLONY_COUNT; i++) {
        while (true) {
            auto xLocation = w(rng);
            auto yLocation = h(rng);
            if (bg.getPixel(xLocation, yLocation).g > 200) {
                locations.emplace_back(xLocation, yLocation);
                break;
            }
        }
    }
    return locations;
}