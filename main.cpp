//
// Created by cstar on 11/3/2026.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "DFS.h"
#include "graph.h"
using namespace std;

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main(int argc, char* argv[])
{
    std::string path= (argc>1)?argv[1]:"data/sample_flights.csv";
    Graph g;
    Stats s;
    if (!loadGraph(path, g, s))
    {
        cout<< "Failed to load graph from: " <<path<< endl; return 1;
    }
    cout<<"Rows Read: "<<s.readRows<<endl;
    cout<<"Rows Kept: "<<s.keptRows<<endl;
    cout<<"Rows Dropped: "<<s.droppedRows<<endl;
    cout<<"Airports: "<<g.numAirports<<endl;
    cout<<"Edges: "<<g.numEdges<<endl;

    string choice;

    while (true) {
        cout << "1. Find route using DFS" << endl;
        cout << "2. Find route using BFS (not implemented)" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice) or choice == "3") {
            break;
        }

        if (choice != "1" and choice != "2") {
            cout << "Choose 1, 2, or 3" << endl;
            continue;
        }

        if (choice == "2") {
            cout << "BFS has not been implemented yet." << endl;
            continue;
        }

        string origin;
        string destination_code;

        cout << "Origin and destination (uppercase, example GNV SEA): ";
        if (!(cin >> origin >> destination_code)) {
            break;
        }

        int startIndex = getAirportIndex(g, origin);
        int end_Index = getAirportIndex(g, destination_code);
        DFSResult result = findDFS(g, startIndex, end_Index);

        if (!result.validQuery) {
            cout << "One or both airport codes were not found.\n";
            continue;
        }

        cout << "DFS: ";

        if (result.found) {
            for (int i = 0; i < static_cast<int>(result.route.size()); i++) {
                if (i != 0) {
                    cout << " -> ";
                }

                cout << getAirportCode(g, result.route[i]);
            }

            cout << " | flights: " << result.flights_in_route;
        } else {
            cout << "No route | flights: N/A";
        }

        cout << " | visited: " << result.airportsVisited
            << " | edges: " << result.edges_examined
            << " | time: " << fixed << setprecision(3)
            << result.timeMicroseconds << " microseconds\n";
    }

    return 0;

}