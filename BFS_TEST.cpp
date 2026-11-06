#include <iostream>
#include <string>
#include <vector>
#include "graph.h"
#include "BFS.h"
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

    // The longer route is inserted first, but BFS should take the direct flight
    addEdge(graph, a, b, "TEST", "1");
    addEdge(graph, a, d, "TEST", "2");
    addEdge(graph, b, c, "TEST", "3");
    addEdge(graph, c, d, "TEST", "4");

    BFSResult result = findBFS(graph, a, d);
    check(result.validQuery and result.found and result.route == vector<int>({a, d}) and result.flights_in_route == 1, "BFS takes direct flight instead of longer first branch");
    check(result.airportsVisited == 4 and result.edges_examined == 3, "counts for direct route");
    check(result.timeMicroseconds >= 0, "nonnegative time");

    result = findBFS(graph, a, a);
    check(result.validQuery and result.found and result.route == vector<int>({a}) and result.flights_in_route == 0 and result.airportsVisited == 1 and result.edges_examined == 0, "same airport");

    result = findBFS(graph, d, a);
    check(result.validQuery and !result.found and result.route.empty() and result.flights_in_route == -1 and result.airportsVisited == 1 and result.edges_examined == 0, "no reverse flight");

    addEdge(graph, c, a, "TEST", "5");
    addEdge(graph, a, b, "TEST", "6");
    addEdge(graph, b, b, "TEST", "7");

    result = findBFS(graph, a, isolated);
    check(result.validQuery and !result.found and result.route.empty() and result.flights_in_route == -1 and result.airportsVisited == 4 and result.edges_examined == 7, "unreachable destination with cycle, duplicate, and self-loop");

    result = findBFS(graph, a, d);
    check(result.found and result.route == vector<int>({a, d}) and result.flights_in_route == 1, "new search resets visited state");

    check(!findBFS(graph, -1, d).validQuery and !findBFS(graph, a, -1).validQuery and !findBFS(graph, graph.numAirports, d).validQuery and !findBFS(graph, a, graph.numAirports).validQuery, "invalid airport indices");

    Graph emptyGraph;
    check(!findBFS(emptyGraph, 0, 0).validQuery, "empty graph");

    Graph branches;
    int start = addAirport(branches, "START");
    int first = addAirport(branches, "FIRST");
    int middle = addAirport(branches, "MID");
    int second = addAirport(branches, "SECOND");
    int end = addAirport(branches, "END");
    addEdge(branches, start, first, "TEST", "1");
    addEdge(branches, first, middle, "TEST", "2");
    addEdge(branches, middle, end, "TEST", "3");
    addEdge(branches, start, second, "TEST", "4");
    addEdge(branches, second, end, "TEST", "5");

    result = findBFS(branches, start, end);
    check(result.found and result.route == vector<int>({start, second, end}) and result.flights_in_route == 2, "shortest route with connecting flights");

    // Equal length routes should follow the order flights were added
    addEdge(branches, first, end, "TEST", "6");
    result = findBFS(branches, start, end);
    check(result.found and result.route == vector<int>({start, first, end}) and result.flights_in_route == 2, "first discovered route wins equal length tie");

    cout << "Failures: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
