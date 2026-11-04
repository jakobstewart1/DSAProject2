//
// Created by cstar on 11/3/2026.
#include <iostream>
#include <fstream>
#include <string>
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

    return 0;

}