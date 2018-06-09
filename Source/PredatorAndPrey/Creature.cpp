#include "Creature.h"


#include "../Util/Random.h"

Creature::Creature()
{
    auto n = Random::get().intInRange(0, 1000);

    if (n > 100)
    {
        m_type = CreatureType::Nothing;
    }
    else if (n > 50)
    {
        m_type = CreatureType::Prey;
    }
    else
    {
        m_type = CreatureType::Predator;
    }
}

sf::Color Creature::getColour() noexcept
{
    if (m_type == CreatureType::Nothing || m_health == 0)
    {
        return sf::Color::Black;
    }
    else
    {
        float normalisedHealth = (float)m_health / (float)MAX_HEALTH;
        uint8_t col = uint8_t(normalisedHealth * 255);

        switch (m_type)
        {
        case CreatureType::Predator:
            return { col, 0, 0 };

        case CreatureType::Prey:
            return { 0, col, 0 };

        default:
            return sf::Color::Black;
        }
    }
}

CreatureType Creature::getType() const noexcept
{
    return m_type;
}

void Creature::setType(CreatureType type) noexcept
{
    m_type = type;
}

void Creature::heal(int amount)
{
    m_health += amount;
    m_health = std::min(m_health, MAX_HEALTH);
}

int Creature::getHealth() const noexcept
{
    return m_health;
}

void Creature::update()
{
    switch (m_type)
    {
    case CreatureType::Predator:
        heal(-1);
        break;

    case CreatureType::Prey:
        heal(1);
        break;

    default:
        break;
    }
}

void Creature::reproduce(Creature& other)
{
    other.m_health = 10;
    other.m_type = CreatureType::Prey;
}

void Creature::move(Creature& other)
{
    other.m_health = m_health;
    other.m_type = m_type;
    m_type = CreatureType::Nothing;
}

void Creature::setHealth(int val) noexcept
{
    m_health = val;
}