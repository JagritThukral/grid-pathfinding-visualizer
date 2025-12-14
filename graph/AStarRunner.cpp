#include "AStarRunner.hpp"
#include "iostream"

AStarRunner::AStarRunner(Graph *g) : graph(g) {
}

void AStarRunner::initialize(Pair s, Pair e) {
    start = s;
    end = e;
    openList = {};
    closedList.clear();
    nodeDetails.clear();
    openList.emplace(0.0f, start);
    nodeDetails[start] = {0, 0, 0, start};
}

// do a* incrementally so we don't freeze our event loop
StepResult AStarRunner::step(std::vector<std::vector<Cell> > &grid) {
    StepResult result{false, false, false};

    if (openList.empty()) {
        result.done = true;
        result.pathFound = false;
        return result;
    }
    // track if made an ui update
    bool changed = false;
    // Get lowest f node
    const Node current = openList.top();
    openList.pop();
    Pair currentPos = current.second;

    if (closedList.contains(currentPos)) return result;
    closedList.insert(currentPos);

    // mark as visited unless it's start/end
    if (!isSpecialCell(grid[currentPos.first][currentPos.second].state)) {
        grid[currentPos.first][currentPos.second].changeState(CellState::Visited);
        changed = true;
    }

    // end reached
    if (currentPos == end) {
        std::cout << "Path found!\n";
        Pair trace = end;
        while (trace != start) {
            if (!isSpecialCell(grid[trace.first][trace.second].state)) {
                grid[trace.first][trace.second].changeState(CellState::Path);
                changed = true;
            }
            trace = nodeDetails[trace].parent;
        }
        result.done = true;
        result.pathFound = true;
        result.changed = changed;
        return result; // finished
    }

    // expand neighbours
    for (const Pair &successor: graph->adjList[currentPos]) {
        if (closedList.contains(successor)) continue;

        const float moveCost = (abs(successor.first - currentPos.first) +
                                abs(successor.second - currentPos.second) == 2)
                                   ? graph->diagonalEdgeLength
                                   : graph->edgeLength;

        const float gNew = nodeDetails[currentPos].g + moveCost;
        const float hNew = graph->heuristic(successor, end);
        const float fNew = gNew + hNew;

        if (!nodeDetails.contains(successor) || fNew < nodeDetails[successor].f) {
            nodeDetails[successor] = {fNew, gNew, hNew, currentPos};
            openList.emplace(fNew, successor);
            if (grid[successor.first][successor.second].state == CellState::Empty) {
                grid[successor.first][successor.second].changeState(CellState::Discovered);
                changed = true;
            }
        }
    }

    result.changed = changed;
    result.done = false;
    result.pathFound = false;
    return result; // still running
}

