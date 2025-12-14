#pragma once
#include <unordered_map>
#include <unordered_set>

#include "grid/Cell.hpp"
#include "utils/PairHash.hpp"
#include "utils/Constants.hpp"


class Graph {
public:
    struct NodeDetails {
        float f, g, h;
        Pair parent;
    };

    std::unordered_map<Pair, std::unordered_set<Pair, PairHash>, PairHash> adjList;
    float edgeLength = 1.0f;
    // under root 2
    float diagonalEdgeLength = 1.41421356f;
    void loadGraphFromGrid(const std::vector<std::vector<Cell>> &grid);
    void addEdge(const Pair& u, const Pair& v);
    void addNode(const Pair &u, std::vector<std::vector<Cell>> &grid);
    void removeNode(const Pair& u);
    [[nodiscard]] float heuristic(Pair current, Pair end) const;
};
