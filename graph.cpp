#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include "graph.h"
using namespace std;

vector<string> split(const string& line){
    vector<string> fields;
    stringstream ss(line);
    string field;
    while (getline(ss, field, ','))
    {
        fields.push_back(field);
    }
    if (!line.empty()&&line.back()==',') fields.push_back("");
    return fields;

}

int getAirportIndex(const Graph& g, const string& code)
{
    auto it=g.codeToIdx.find(code);
    return it==g.codeToIdx.end()? -1 : it->second;
}
const std::string& getAirportCode(const Graph& g, int idx)
{
    return g.codes[idx];
}
int addAirport(Graph& g, const string& code)
{
    auto it=g.codeToIdx.find(code);
    if (it!=g.codeToIdx.end())
    {
        return it->second;
    }
    int idx=g.numAirports++;
    g.codeToIdx[code]=idx;
    g.codes.push_back(code);
    g.adj.emplace_back();
    return idx;
}
void addEdge(Graph& g, int from, int to, const std::string& airline, const string& flightNum)
{
    g.adj[from].push_back({to,airline,flightNum});
    g.numEdges++;
}

bool loadGraph(const std::string& path, Graph& g, Stats& stats)
{
    ifstream file(path);
    if (!file.is_open()) return false;

    string headerLine;
    getline(file,headerLine);
    if (!headerLine.empty()&& headerLine.back() == '\r')
    {
        headerLine.pop_back();
    }
    vector<string> header=split(headerLine);

    unordered_map<string, int> columns;
    for (int i=0;i<header.size();i++)
    {
        columns[header[i]]=i;
    }

    vector<string> required_cats={
        "ORIGIN", "DEST", "CANCELLED", "DIVERTED","OP_UNIQUE_CARRIER",
        "OP_CARRIER_FL_NUM"
    };
    for (const string&name:required_cats)
    {
        if (columns.find(name)==columns.end())
        {
            cerr<<"Missing column: "<<name<<endl;
            return false;
        }
    }

    int originCol=columns["ORIGIN"];
    int destCol=columns["DEST"];
    int cancelledCol=columns["CANCELLED"];
    int divertedCol=columns["DIVERTED"];
    int airlineCol=columns["OP_UNIQUE_CARRIER"];
    int flightCol=columns["OP_CARRIER_FL_NUM"];


    string line;
    while (getline(file,line))
    {
        if (line.empty()) continue;
        if (!line.empty()&&line.back() == '\r')
        {
            line.pop_back();
        }
        stats.readRows++;
        vector<string> fields = split(line);
        if (fields.size()!=header.size()){
            stats.droppedRows++;
            continue;
        }
        string origin=fields[originCol];
        string dest=fields[destCol];
        string airline=fields[airlineCol];
        string flight=fields[flightCol];

        bool cancelled=false, diverted=false;
        try
        {
            cancelled=stod(fields[cancelledCol])==1.0;
            diverted=stod(fields[divertedCol])==1.0;
        } catch (...)
        {
            stats.droppedRows++;
            continue;
        }

        if (origin.empty()||dest.empty()||cancelled||diverted){ stats.droppedRows++; continue;}
            stats.keptRows++;
            int fromIdx=addAirport(g, origin);
            int toIdx=addAirport(g, dest);
            addEdge(g, fromIdx, toIdx, airline, flight );



    }

return true;

}