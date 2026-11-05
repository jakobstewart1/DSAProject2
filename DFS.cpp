#include "DFS.h"
#include <chrono>

DFSResult findDFS(const Graph& graph, int start, int destination) {
    DFSResult result;
    int airport_count = static_cast<int>(graph.adj.size());

    // Invalid queries do not start the timer or visit any airports.
    if (start < 0 || destination < 0 || start >= airport_count ||
        destination >= airport_count) {
        return result;
    }
    result.validQuery = true;
    auto startTime = std::chrono::steady_clock::now();

    std::vector<bool> visited(airport_count, false);
    std::vector<int> parent(airport_count, -1);
    // Remember where to resume each airport's neighbor list after backtracking.
    std::vector<std::size_t> next_edge(airport_count, 0);
    std::vector<int> airportStack;

    airportStack.push_back(start);
    visited[start] = true;
    result.airportsVisited = 1;

    while (!airportStack.empty()) {
        int currentAirport = airportStack.back();
        if (currentAirport == destination) {
            result.found = true;
            break;
        }

        if (next_edge[currentAirport] == graph.adj[currentAirport].size()) {
            airportStack.pop_back(); // No neighbors left: backtrack.
        } else {
            int nextAirport = graph.adj[currentAirport][next_edge[currentAirport]].to;
            next_edge[currentAirport]++;
            result.edges_examined++;

            // The graph builder must provide valid destination indices.
            if (!visited[nextAirport]) {
                visited[nextAirport] = true;
                result.airportsVisited++;
                parent[nextAirport] = currentAirport;
                airportStack.push_back(nextAirport);
            }
        }
    }

    // Include search-state setup and traversal, but exclude route formatting
    // and reconstruction. BFS should use the same timing boundary.
    auto end_time = std::chrono::steady_clock::now();
    result.timeMicroseconds =
        std::chrono::duration<double, std::micro>(end_time - startTime).count();

    if (result.found) {
        std::vector<int> backwards;
        int airport = destination;
        while (airport != -1) {
            backwards.push_back(airport);
            airport = parent[airport];
        }
        for (int i = static_cast<int>(backwards.size()) - 1; i >= 0; i--) {
            result.route.push_back(backwards[i]);
        }
        result.legs = static_cast<int>(result.route.size()) - 1;
    }
    return result;
}

