//
// Created by cstar on 11/3/2026.
//

#ifndef DSAPROJECT2_GRAPH_H
#define DSAPROJECT2_GRAPH_H
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

struct Edge
{
    int to;
    std::string airline;
    std::string flightNum;

};
struct Stats
{
    ;
    long long readRows=0;
    long long keptRows=0;
    long long droppedRows=0;
};

struct Graph
{
    int numAirports=0;
    long long numEdges=0;
    std::vector<std::string> codes;
    std::unordered_map<std::string, int> codeToIdx;
    std::vector<std::vector<Edge>> adj;
};

bool loadGraph(const std::string& path, Graph& g, Stats& stats);
std::vector<std::string> split(const std::string& line);
int getAirportIndex(const Graph& g, const std::string& code);
const std::string & getAirportCode(const Graph& g, int idx);
int addAirport(Graph& g, const std::string& code);
void addEdge(Graph& g, int from, int to, const std::string& airline, const std::string& flightNum);
#endif //DSAPROJECT2_GRAPH_H