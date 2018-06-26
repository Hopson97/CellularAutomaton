#pragma once

#include <vector>
#include <array>
#include <optional>
#include <memory>

#include "../CellularAutomaton.h"

class InputMode;

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

        void setCell(int x, int y, Cell cell);
        Cell getCell(int x, int y);

        void input(const sf::Event& e) override;
        void update() override;

        const Config& getConfig() const;
        CellPointInfo getCellPointInfo(const sf::Vector2i& cellPoint);

    private:
        std::optional<sf::Vector2i> getMouseInputPosition() const;
        void onRenderCells(sf::RenderWindow& window) override;

        std::unique_ptr<InputMode> m_inputMode;
        std::vector<Cell> m_cells;
        bool m_isInEditMode = true;
};