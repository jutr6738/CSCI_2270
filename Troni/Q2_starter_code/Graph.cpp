#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void Graph::addEdge(string source, string target){
    for(unsigned int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == source){
            for(unsigned int j = 0; j < vertices.size(); j++){
                if(vertices[j]->name == target && i != j){
                    adjVertex av;
                    av.v = vertices[j];
                    vertices[i]->adj.push_back(av);
                }
            }
        }
    }
}

void Graph::addVertex(string vName){
    bool found = false;
    for(unsigned int i = 0; i < vertices.size(); i++){
        if(vertices[i]->name == vName){
            found = true;
            cout<<vertices[i]->name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex * v = new vertex;
        v->name = vName;
        v->distance = 0;
        vertices.push_back(v);
    }
}

void Graph::displayEdges(){
    for(unsigned int i = 0; i < vertices.size(); i++){
        cout<<vertices[i]->name<<":"<<endl;
        for(unsigned int j = 0; j < vertices[i]->adj.size(); j++){
            cout<<" --> "<< vertices[i]->adj[j].v->name <<endl;
        }
        cout<<endl;
    }
}

void DFTraversal(vertex *n)
{
    n->visited = true;

    for(int x = 0; x < n->adj.size(); x++ ) //iterate over all neighbors of n
    {
        if (n->adj[x].v->visited == false)  //neighbor of n is not visited 
        { 
            DFTraversal(n->adj[x].v); //recursively call 
            
        }
    }

}


bool Graph::isStronglyConnected(){
    /* 
    Implement this function. 
    This function returns true if the graph is strongly connected. Otherwise, returns false.
    */

   


  //Step1: Get initial_components. 
  for (int i=0; i<vertices.size(); i++)  //iteratve over all vertices
  {
      if  (vertices[i]->adj.size() != vertices.size())
      {
          cout << "not" << endl;
      }
  }

}