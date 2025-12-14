#include "Cell.hpp"

Cell::Cell() {
    rect.setOutlineThickness(1);
    rect.setOutlineColor(sf::Color::Black);
    rect.setFillColor(COLOR_DEFAULT);
    rect.setSize(cellSize);
    state = CellState::Empty;
}

void Cell::changeState(CellState newState) {
    state = newState;
    switch (newState) {
        case CellState::Start: rect.setFillColor(COLOR_START);
            break;
        case CellState::End: rect.setFillColor(COLOR_END);
            break;
        case CellState::Wall: rect.setFillColor(COLOR_WALL);
            break;
        case CellState::Visited: rect.setFillColor(COLOR_VISITED);
            break;
        case CellState::Discovered: rect.setFillColor(COLOR_DISCOVERED);
            break;
        case CellState::Path: rect.setFillColor(COLOR_PATH);
            break;
        case CellState::Empty: rect.setFillColor(COLOR_DEFAULT);
            break;
    }
}
