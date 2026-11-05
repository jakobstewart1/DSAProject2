#include "DFS.h"
#include <chrono>
#include <cstddef>
using namespace std;

DFSResult findDFS(const Graph& graph, int start, int destination) {
    DFSResult result;
    int airport_count = static_cast<int>(graph.adj.size());
    
    // using getAirportIndex when an airport code is unknown it becomes -1
    if (start < 0 or destination < 0 or start >=airport_count or destination >= airport_count) {
        return result;
    }

    result.validQuery = true;
    auto startTime = std::chrono::steady_clock::now();


    vector<bool> visited(airport_count, false);
    vector<int> parent(airport_count, -1);
    //Saves the edge that should be checked next once it returns to an airport
    vector<size_t> next_edge(airport_count, 0);
    vector<int> airportStack;
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
            airportStack.pop_back();
        }else{
            int nextAirport = graph.adj[currentAirport][next_edge[currentAirport]].to;
            next_edge[currentAirport]++;
            result.edges_examined++;

            if (!visited[nextAirport]) {
                visited[nextAirport] = true;
                airportStack.push_back(nextAirport);
                parent[nextAirport] = currentAirport;
                result.airportsVisited++;
            }
        }
    }
     // Times the search setup and traversal
     //This also makes sure that the time taken to build the route is not included in the search time
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
