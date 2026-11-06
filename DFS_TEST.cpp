#include <iostream>
#include <string>
#include <vector>
#include "graph.h"
#include "DFS.h"
using namespace std;

int failures = 0;

void check(bool passed, const string& testName) {
    if (passed) {
        cout << "Test " << testName << " passed." << endl;
    } else {
        cout << "Test " << testName << " failed." << endl;
        failures++;
    }
}

int main(){
    Graph graph;

    int a = addAirport(graph, "AAA");
    int b = addAirport(graph, "BBB");
    int c = addAirport(graph, "CCC");
    int d = addAirport(graph, "DDD");
    int isolated = addAirport(graph, "ISO");

    // A has 2 routes to D: A->B->C->D and A->D. DFS should follow the first route, even though it is longer.
    // Add A->B first because DFS checks flights in insertion order
    addEdge(graph, a, b, "TEST", "1");
    addEdge(graph, a, d, "TEST", "2");
    addEdge(graph, b, c, "TEST", "3");
    addEdge(graph, c, d, "TEST", "4");


        DFSResult result = findDFS(graph, a, d);

    //DFS should reach D thru B and C
    //Danny make sure BFS takes A->D
    check(result.validQuery and result.found and
          result.route == vector<int>({a, b, c, d}) and result.flights_in_route == 3,
          "DFS follows first branch despite a direct flight");

    check(result.airportsVisited == 4 and result.edges_examined == 3,
          "counts for first route");

    check(result.timeMicroseconds >= 0, "nonnegative time");

    result = findDFS(graph, a, a);

    check(result.found and result.route == vector<int>({a}) and
          result.flights_in_route == 0 and result.airportsVisited == 1 and result.edges_examined == 0,"same airport");

    result = findDFS(graph, d, a);

    check(result.validQuery and !result.found and result.route.empty() and result.flights_in_route == -1 and result.airportsVisited == 1 and result.edges_examined == 0,"no reverse flight");

    addEdge(graph, c, a, "TEST", "5");
    addEdge(graph, a, b, "TEST", "6");
    addEdge(graph, b, b, "TEST", "7");

    result = findDFS(graph, a, isolated);

    check(!result.found and result.route.empty() and result.flights_in_route == -1 and result.airportsVisited == 4 and result.edges_examined == 7, "unreachable destination with cycle, duplicate, and self-loop");

    result = findDFS(graph, a, d);

    check(result.route == vector<int>({a, b, c, d}) and result.edges_examined == 3,
          "new search resets visited state");

    check(!findDFS(graph, -1, d).validQuery and
          !findDFS(graph, a, graph.numAirports).validQuery,
          "invalid airport indices");

    Graph emptyGraph;
    check(!findDFS(emptyGraph, 0, 0).validQuery, "empty graph");

    Graph branch_graph;

    //Insertion order gives Start Dead Mid and End indexes 0, 1, 2, and 3
    addAirport(branch_graph, "START");
    addAirport(branch_graph, "DEAD");
    addAirport(branch_graph, "MID");
    addAirport(branch_graph, "END");

    addEdge(branch_graph, 0, 1, "TEST", "1");
    addEdge(branch_graph, 0, 2, "TEST", "2");
    addEdge(branch_graph, 2, 3, "TEST", "3");

    //DFS tries DEAD first, but it is a dead end, so it backtracks and finds the route through MID to END.
    //Dead counts towards 4 airports visited and 3 edges examined. but its absent from the final route.
    result = findDFS(branch_graph, 0, 3);

    check(result.found and result.route == vector<int>({0, 2, 3}) and
          result.flights_in_route == 2 and result.airportsVisited == 4 and
          result.edges_examined == 3,
          "backtracking excludes dead end from route");

    cout << "Failures: " << failures << '\n';

    //code that will allow it to report whenever a failed test run happens
    // if checks fail 
    return failures == 0 ? 0 : 1;
}

