#pragma once
#include <SFML/Graphics.hpp>
#include "utils/Constants.hpp"

enum class CellState {
    Empty, Wall, Start, End, Visited, Discovered, Path
};

class Cell {
public:
    sf::RectangleShape rect;
    CellState state;
    Pair index;
    Cell();
    void changeState(CellState newState);
};

inline bool isValidCell(int r, int c, const std::vector<std::vector<Cell>>& grid) {
    return r >= 0 && r < gridRows &&
           c >= 0 && c < gridCols &&
           grid[r][c].state != CellState::Wall;
}

inline bool isSpecialCell(const CellState s) {
    return s == CellState::Start || s == CellState::End;
}