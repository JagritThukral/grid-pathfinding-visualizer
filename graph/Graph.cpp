#include "Graph.hpp"

#include "grid/Cell.hpp"


void Graph::loadGraphFromGrid(const std::vector<std::vector<Cell>> &grid) {
    for (int row = 0; row < gridRows; ++row) {
        for (int col = 0; col < gridCols; ++col) {
            // add valid neighbours of cell as nodes in graph
            for (auto [dr,dc]: directions) {
                int nr = row + dr;
                int nc = col + dc;
                if (isValidCell(nr, nc, grid)) {
                    addEdge({row, col}, {nr, nc});
                }
            }
        }
    }
}

void Graph::addEdge(const Pair& u, const Pair& v) {
    adjList[u].insert(v);
    adjList[v].insert(u);
}
void Graph::addNode(const Pair &u,  std::vector<std::vector<Cell>> &grid) {
    if (adjList.contains(u)) return;
    adjList[u] = {};
    // Connect to all valid neighbors
    for (const auto& dir : directions) {
        int nr = u.first + dir.first;
        int nc = u.second + dir.second;
        if (isValidCell(nr, nc, grid)) {
            Pair neighbor = {nr, nc};
            // Only connect to existing nodes in the graph
            if (adjList.contains(neighbor)) {
                addEdge(u, neighbor);
            }
        }
    }
}
// Remove a node entirely
void Graph::removeNode(const Pair& u) {
    if (!adjList.contains(u)) return;
    // remove node from all neighbour's adjList
    for (const auto& neighbor : adjList[u]) {
        adjList[neighbor].erase(u);
    }
    adjList.erase(u);
}

float Graph::heuristic(const Pair current, const Pair end) const {
    const auto dx = static_cast<float>(abs(current.first - end.first));
    const auto dy = static_cast<float>(abs(current.second - end.second));
    // Diagonal Distance (8 direction movement)
    return edgeLength * (dx + dy) + (diagonalEdgeLength - 2 * edgeLength) * std::min(dx, dy);
    // Manhattan  distance (4 direction movement)
    //return edgeLength * (dx + dy);
}
