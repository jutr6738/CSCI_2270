#include <iostream>
#include "Graph.hpp"
#include <vector> // for vertex and edge lists
#include <queue>
#include <iostream>  

using namespace std;

//makes a connection between v1 and v2
void Graph::addEdge(string v1, string v2)
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
                    newedge1to2.v = vertices[j];
                    vertices[i]->adj.push_back(newedge1to2);

                    //adding the edge to v2's list
                    adjVertex newedge2to1;
                    newedge2to1.v= vertices[i]; 
                    vertices[j]->adj.push_back(newedge2to1); 
                }
            }
        }
    }
}


//function to add a new vertex 'name' to the graph 
void Graph::addVertex(string name)
{
    //checking that vertex does not already exist
    bool found =false; 
    for (int i=0; i< vertices.size(); i++)
    {
        if (vertices[i]-> name == name)
        {
            cout << "Error. Vertex already exists." << endl;
            found = true;
        }
    }
    //since it doesn't exist, add it to the vector of vertices
    if (found == false)
    {
        vertex * addthis= new vertex;
        addthis->name = name;
        addthis-> visited= false;
        vertices.push_back(addthis);
    }

}

//displays all edges in the graph
void Graph::displayEdges()
{
    for (int i=0; i<vertices.size(); i++)
    {
        cout << vertices[i]->name << " --> ";

        for (int j=0; j< vertices[i]->adj.size(); j++)
        {
            cout << vertices[i]->adj[j].v->name << " ";
        }
        cout << endl;
    }

}


//breadth first traversal from sourceVertex
void Graph::breadthFirstTraverse(string sourceVertex)
{
    vertex * sv; //pointer that will be used to point to the starting vertex 

    for (int i=0; i<vertices.size(); i++)   //looping through all the vertexs in the graph to find the one that correspond with the name 
    {
        if (vertices[i]->name == sourceVertex)
        {
            sv= vertices[i]; //this is the starting vertex
        }
    }
    queue <vertex*> q; //creating a queue 

    q.push(sv);     //pushing the starting vertex onto the queue
    sv->visited = true; //marking it as visited

    cout<< "Starting vertex (root): " << sv->name << "-> "; 

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
                
                cout << curr->adj[i].v->name <<"("<< curr->adj[i].v->distance <<")"<< " ";
            }
        }
    } 

}

void depthFirstTraverse(vertex *start)
{
    start->visited= true;

    for (int j=0; j<start->adj.size(); j++)
    {
        if (start->adj[j].v->visited == false)
        {
            depthFirstTraverse(start->adj[j].v);
        }
    }
}


//counts the number of connected components in the graph aka the number of subgraphs
int Graph::getConnectedComponents()
{
    int count = 0; 

    for (int i=0; i<vertices.size(); i++)
    {
        vertices[i]->visited = false;
    }
    for (int i=0; i<vertices.size(); i++)
    {
        if (vertices[i]->visited ==false)
        {
            depthFirstTraverse(vertices[i]);
            count++;
        }
    } 
    return (count);  
}