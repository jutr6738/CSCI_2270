#include <iostream>
#include "Graph.hpp"

using namespace std;

int main() {
    Graph G;

    G.addVertex("1");
    G.addVertex("2");
    G.addVertex("3");
    G.addVertex("4");
    G.addVertex("5");
    G.addVertex("6");
    
    G.addEdge("1", "2", 7);
    G.addEdge("1", "3", 9);
    G.addEdge("1", "6", 14);
    G.addEdge("2", "3", 10);
    G.addEdge("2", "4", 15);
    G.addEdge("4", "3", 11);
    G.addEdge("4", "5", 16);
    G.addEdge("5", "6", 9);
    G.addEdge("6", "3", 2);
    

    G.prettyPrint();
    G.depthFirstTraverse("1");    

    cout << "BFS from 1" << endl;
    G.breadthFirstTraverse("1");
    G.printDistance();

    cout << "Dijsktra from 1" << endl;
    G.dijkstraTraverse("1");
    G.printDistance();

    
    
    return 0;
}