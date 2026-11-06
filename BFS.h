#ifndef ROUTE54_BFS_H
#define ROUTE54_BFS_H

#include "graph.h"
#include <vector>

struct BFSResult {
    bool validQuery = false;
    bool found = false;
    std::vector<int> route;
    int flights_in_route = -1;
    int airportsVisited = 0;
    long long edges_examined = 0;
    double timeMicroseconds = 0.0;

};

BFSResult findBFS(const Graph &graph, int start, int destination);

#endif //ROUTE54_BFS_H
