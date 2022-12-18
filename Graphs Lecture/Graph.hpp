#pragma once // include this file only once

#include <iostream>
#include <vector> // to store list of vertices and edges

using namespace std;

struct Edge; // declare the edge to be defined later

struct Vertex
{
    string name;
    vector<Edge *> edgeList; 
    bool visited;
    int distance;
};

struct Edge
{
    Vertex *dst; // destination of this vertex
    int weight;  // for weighted graphs
};

class Graph
{
private:
    vector<Vertex *> vertexList; 
    void depthFirstTraverseHelper(Vertex *p_u);

public:
    Vertex* getVertex(string u);
    
    void addVertex(string u);
    void addEdge(string u, string v);
    void prettyPrint();
    

    void depthFirstTraverse(string u);
    void breadthFirstTraverse(string u);

};
