#pragma once

#include <array>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

class Keyboard {
    public:
        Keyboard();

        void update(sf::Event e);
        bool isKeyDown(sf::Keyboard::Key key) const;


    private:
        std::array<bool, sf::Keyboard::KeyCount> m_keys;
};