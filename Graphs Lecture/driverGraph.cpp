#include <iostream>
#include "Graph.hpp"

using namespace std;

int main() {
    Graph G;

    G.addVertex("A");
    G.addVertex("B");
    G.addVertex("C");
    G.addVertex("D");
    G.addVertex("E");
    G.addVertex("F");
    G.addVertex("G");
    G.addVertex("H");
    
    G.addEdge("A", "B");
    G.addEdge("A", "C");
    G.addEdge("B", "D");
    G.addEdge("B", "E");
    G.addEdge("E", "F");

    G.addEdge("G", "H");
    

    G.prettyPrint();

    G.breadthFirstTraverse("A");
    G.depthFirstTraverse("A");    
    
    return 0;
}