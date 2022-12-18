#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include <queue>


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
        vertices.push_back(v);
    }
}

void Graph::display(){
    cout<<"vertex"<<":"<<"color"<<endl;
    for(unsigned int i = 0; i < vertices.size(); i++){
        cout<<vertices[i]->name<<":"<<vertices[i]->color<<endl;

    }
}



//breadth first traversal from sourceVertex
void breadthFirstTraverse(vertex * sv)
{
    
    queue <vertex*> q; //creating a queue 

    q.push(sv);     //pushing the starting vertex onto the queue
    sv->visited = true; //marking it as visited

    while (!q.empty())
    {
        vertex * curr = q.front();
        q.pop();

        for (int i= 0; i < curr->adj.size(); i++)   //traversing through all the adjacent/neighbor nodes 
        {
            if (curr->adj[i].v->visited== false) //if we haven't visited that neighbor we will.. 
            {
                q.push(curr->adj[i].v);   //push the neighbor onto the queue
                curr->adj[i].v->visited= true; //mark the neighbor as visited
                curr->adj[i].v->distance= curr->distance+1; //updating the distance of the neighbor node
                if (curr->adj[i].v->distance%2 ==0)
                {
                    curr->adj[i].v->color= "black";
                }
                else if (curr->adj[i].v->distance%2 ==1)
                {
                    curr->adj[i].v->color= "red";
                }
                
            }
        }
    } 

}

void Graph::color(string source){
  
  vertex *start;

//initializing all vertex to white and finding the source vertex
  for (int i=0; i< vertices.size(); i++)
  {
      vertices[i]->color = "white"; 
      if (vertices[i]->name==source)
      {
         start= vertices[i]; 
      }
  }
  //coloring source black
  start->color= "black";
  //coloring adj red
  for (int i= 0; i< start->adj.size(); i++ )
  {
      start->adj[i].v->color="red";
  }
//bft to color even distance vertices black and odd distance vertices red
  breadthFirstTraverse(start);

}
