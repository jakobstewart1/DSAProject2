#include "BFS.h"
#include <chrono>
#include <queue>
using namespace std;

BFSResult findBFS(const Graph& graph, int start, int destination) {
    BFSResult result;
    int airport_count = static_cast<int>(graph.adj.size());

    if (start < 0 or destination < 0 or start >= airport_count or destination >= airport_count) {
        return result;
    }

    result.validQuery = true;
    auto startTime = std::chrono::steady_clock::now();

    vector<bool> visited(airport_count, false);
    vector<int> parent(airport_count, -1);
    queue<int> airportQueue;
    airportQueue.push(start);
    visited[start] = true;
    result.airportsVisited = 1;

    while (!airportQueue.empty()) {
        int currentAirport = airportQueue.front();
        airportQueue.pop();

        if (currentAirport == destination) {
            result.found = true;
            break;
        }

        for (const Edge& edge : graph.adj[currentAirport]) {
            int nextAirport = edge.to;
            result.edges_examined++;

            if (!visited[nextAirport]) {
                visited[nextAirport] = true;
                airportQueue.push(nextAirport);
                parent[nextAirport] = currentAirport;
                result.airportsVisited++;
            }
        }
    }

    // Time the search setup and traversal, before building the route
    auto end_time = std::chrono::steady_clock::now();
    result.timeMicroseconds = std::chrono::duration<double, std::micro>(end_time - startTime).count();

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

        result.flights_in_route = static_cast<int>(result.route.size()) - 1;
    }

    return result;
}
