#ifndef ROUTE54_DFS_H
#define ROUTE54_DFS_H

#include "graph.h"
#include <vector>

struct DFSResult {
    bool validQuery = false;
    bool found = false;
    std::vector<int> route;
    int legs = -1;
    int airportsVisited = 0;
    long long edges_examined = 0;
    double timeMicroseconds = 0.0;
};

DFSResult findDFS(const Graph& graph, int start, int destination);

#endif

