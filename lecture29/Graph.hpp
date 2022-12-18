#pragma once // include this file only once

#include <iostream>
#include <vector> // to store list of vertices and edges

using namespace std;

struct Edge; // declare the edge to be defined later

struct Vertex
{
    string name; // Name of the vertes
    vector<Edge *> edgeList;  // List of outgoing edges 
    bool visited; // To keep track of visit status in BFT/DFT 
    int distance; // To keep track of distance in a shortest path
    Vertex* prev; // To keep track of previous node in a shortest path 
};

struct Edge
{
    Vertex* dst; // Destination of this Edge
    int weight;  // Weight of this Edge
};

class Graph
{
private:
    vector<Vertex *> vertexList; // List of vertices 
    void depthFirstTraverseHelper(Vertex *p_u); // Helper function for DFT 

public:
    Vertex* getVertex(string u);
    
    void addVertex(string u);
    void addEdge(string u, string v);
    void addEdge(string u, string v, int w);

    void prettyPrint();
    

    void depthFirstTraverse(string s);
    void breadthFirstTraverse(string s);
    void dijkstraTraverse(string s);
    void printDistance();
    void clearDisance();
};
