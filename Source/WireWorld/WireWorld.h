#pragma once

#include <vector>
#include <array>
#include <optional>

#include "../CellularAutomaton.h"

class WireWorld : public CellularAutomaton
{
        enum class Cell
        {
            Empty,
            Head,
            Tail,
            Conductor
        };
        
        struct CellPointInfo
        {
            int x;
            int y;
            int index;
            Cell* cell;
        };
        

        const std::array<sf::Color, 4> m_cellColours;

    public:
        WireWorld(const Config& config, const Application& app);

        void input(const sf::Event& e) override;
        void update() override;


    private:
        CellPointInfo getCellPointInfo(const sf::Vector2i& cellPoint);
        void onRenderCells(sf::RenderWindow& window) override;

        void mouseInput(const sf::Event& e);
        std::optional<sf::Vector2i> getMouseInputPosition() const;

        std::vector<Cell> m_cells;

        sf::Vector2i m_inputBegin;
        sf::Vector2i m_inputEnd;
        std::vector<sf::Vector2i> m_inputPoints;
        sf::RectangleShape m_inputGhost;

        bool m_isInEditMode = true;

        bool m_isInEraseMode = false;
        bool m_isInLineMode = false;
        bool m_isDoingLineInput = false;
};