#include <iostream>
#include "graph.hpp"
#include <vector> 

using namespace std;

  
  //makes a connection between v1 and v2
void Graph::addEdge(string v1, string v2, int num)
{
    for (int i=0; i< vertices.size(); i++)   //searching the vector of vertices to find v1
    {   
        if (vertices[i]-> name == v1)   //found it
        {
            for (int j=0; j<vertices.size(); j++)   //searching the vector of vertices to find v2
            {
                if (vertices[j]->name ==v2) //found it
                {
                    //now add the edges to the adjacency vectors for both v1 and v2

                    //adding the edge to v1's list
                    adjVertex newedge1to2;
                    newedge1to2.weight = num; 
                    newedge1to2.v = vertices[j];
                    vertices[i]->adj.push_back(newedge1to2);

                    //adding the edge to v2's list
                    adjVertex newedge2to1;
                    newedge2to1.weight=num; 
                    newedge2to1.v= vertices[i]; 
                    vertices[j]->adj.push_back(newedge2to1); 
                }
            }
        }
    }
}



//helper function for depthFirstTraversal
void DFThelper(vertex *start)
{
    start->visited= true;
    cout << start-> name << " -> ";

    for (int j=0; j<start->adj.size(); j++)
    {
        if (start->adj[j].v->visited == false)
        {
            start->distance += start->adj[j].weight;

            DFThelper(start->adj[j].v);
        }
    }
}

//uses depth first traversal from sourceVertex to travers the graph and print the city name and corresponding distance from sourceVertex 
//calls DFThelper
void Graph::depthFirstTraversal(string sourceVertex)
{
    vertex*start; 
    //finding the source vertex
    for (int i=0; i<vertices.size(); i++)
    {
        if (vertices[i]->name==sourceVertex)
        {
            start= vertices[i]; 
        }
    }
    
    DFThelper(start);
    cout << "DONE ";
}


//uses Dijkstra's algorithm to compute the single source shortest path in the graph from the start city to all other nodes in its component
void Graph::dijkstraTraverse(string sourceVertex)
{
    vertex*start; 

    //finding the sourceVertex
    for (int i=0; i<vertices.size(); i++)
    {
        if (vertices[i]->name==sourceVertex)
        {
            start= vertices[i]; 
        }
    }

    /* Implement Dijsktra Algorithm */
    for (int i=0; i< vertices.size(); i++)
    {
        vertices[i]->distance = INT8_MAX;    //initializing all distance to something huge
        vertices[i] -> pred= 0; //initializing all previous vertexs as nothing 
        vertices[i]-> visited = false; //initializing all as unvisited
    } 

      start-> distance =0;    //make our start vertex distance 0
      start->visited= true; //make our start vertex as visited

    vector<vertex*> solvedList;   //vector of vertex pointers that wwill hold the vertexes where we already know the distance to them
    solvedList.push_back(start); 

    bool solved =false;

    while (!solved) //will run until we have all the distances of all of the nodes //iterating through all the nodes in the solved list until we find the minimum distance 
      {
          int minDist = INT8_MAX;
          vertex * minVertex= 0;
          solved = true; 

          for (int i = 0; i < solvedList.size(); i++)   //looking at everthing in the solved list and looking at each of the distances 
          {
              vertex * currinsolvedlist = solvedList[i];
              for (int j=0; j< currinsolvedlist->adj.size(); j++)
              {
                  vertex * someedgeofcurr= currinsolvedlist->adj[j].v; 
                  int w= currinsolvedlist->adj[j].weight; 
                  if (!someedgeofcurr -> visited)
                  {
                      if (minDist > currinsolvedlist->distance + w)
                      {
                          minDist= currinsolvedlist -> distance + w;
                          minVertex= someedgeofcurr;
                          solved = false; 
                      }
                  }
              }
          }
          if (!solved)
          {
              minVertex->distance = minDist;
              minVertex -> visited= true;
              solvedList.push_back(minVertex); 
          }
      }

}

//prints the shortest path found between city 1 and city 2 by involving dijkstraTraverse
void Graph:: shortestPath(string start, string end)
{
    dijkstraTraverse(start);

    //finding the end vertex
    vertex* endV;
    for (int i=0; i<vertices.size(); i++)
    {
        if (vertices[i]->name==end)
        {
            endV=vertices[i];
        }
    }
    vector<string>path;

    vertex * curr = endV;
    path.push_back(end);
   while (curr->name != start) 
    {
        path.push_back(curr->pred->name);
        curr = curr->pred;
    }

    for (int i=path.size(); i>0; i--)
    {
        cout << path[i-1] << " -> " ;
    }

    cout << "DONE [" << endV->distance << "]" << endl;
}



