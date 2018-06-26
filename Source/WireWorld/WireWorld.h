#pragma once

#include <vector>
#include <array>
#include <optional>

#include "../CellularAutomaton.h"
#include "InputMode.h"

class WireWorld : public CellularAutomaton
{
        const std::array<sf::Color, 4> m_cellColours;
    public:
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

    public:
        WireWorld(const Config& config, const Application& app);

        CellPointInfo getCellPointInfo(const sf::Vector2i& cellPoint);
        std::optional<sf::Vector2i> getMouseInputPosition() const;
        void setCell(int x, int y, Cell cell);

        void input(const sf::Event& e) override;
        void update() override;

    private:
        void onRenderCells(sf::RenderWindow& window) override;

        void mouseInput(const sf::Event& e);

        std::vector<Cell> m_cells;

        sf::Vector2i m_inputBegin;
        sf::Vector2i m_inputEnd;
        std::vector<sf::Vector2i> m_inputPoints;
        sf::RectangleShape m_inputGhost;

        bool m_isInEditMode = true;

        bool m_isInEraseMode = false;
        bool m_isInLineMode = false;
        bool m_isDoingLineInput = false;

        PointInputMode test;
};