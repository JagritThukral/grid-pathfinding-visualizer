#pragma once
#include "Graph.hpp"
#include "grid/Cell.hpp"
#include <queue>
struct StepResult {
    bool changed;
    bool done;
    bool pathFound;
};
class AStarRunner {
public:

    using Node = std::pair<float, Pair>;
    std::priority_queue<Node, std::vector<Node>, std::greater<>> openList;
    std::unordered_set<Pair, PairHash> closedList;
    std::unordered_map<Pair, Graph::NodeDetails, PairHash> nodeDetails;
    Graph* graph;
    Pair start, end;

    explicit AStarRunner(Graph *g);

    void initialize(Pair start, Pair end);

    StepResult step(std::vector<std::vector<Cell> > &grid);
};
