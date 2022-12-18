#include <iostream>
#include "Graph.hpp"
#include <vector> // for vertex and edge lists
#include <queue>  // for breadth first traversal

using namespace std;

Vertex *Graph::getVertex(string u) //if a vertex with that name existsm then return a pointer to that vertex 
{

    for (int i=0; i < vertexList.size(); ++i)   //loop over the whole list of vertices 
    {
        if (vertexList[i] -> name ==u)  //if we find it
        {
            return vertexList[i];   //return the pointer to that 
        }
    }

    return 0; //if no vertex is found that matches that name, then will return 0

}

void Graph::addVertex(string u)
{
   if (getVertex(u) ==0) //if vertex with the same name is not already in the graph, then we will add vertex
   {
       Vertex * adding = new Vertex();
       adding -> name = u;
       adding -> visited = false;
       adding -> distance = -1;

       vertexList.push_back(adding);

   }
   else //vertex with that name already exists so print error message
   {
       cerr << "vertex" << u << "already exists" << endl;
   }

}

void Graph::addEdge(string u, string v)
{
    // If u = v, ignore because we will assume a node is connected to itself
    if (u==v)
    {
        return; 
    }

    //  Else   
    else
    {
        Vertex * ptrU = getVertex(u);
        Vertex * ptrV = getVertex(v);

        if (ptrU == 0 || ptrV ==0) //check if both vertices are in the Graph
        {
            cerr << "One of the vertices is not in the graph" << endl;
            return;
        }
        else //both vertices are there so we want to add the edges in both directions becasue this is an undirected graph
        {
            //first check if an edge is already bw u-> v (sometimes you might want to have multiple edges between vertices, but not in this case)
            for (int i=0; i < ptrU -> edgeList.size(); i++)
            {
                if (ptrU ->edgeList[i]->dst == ptrV) //edge already exists between u and v
                {
                    cerr<< "edge already exists" << endl;
                    return;
                }
            }
            //since there is not already an edge bw u and v we will add one 
            Edge * edgeFromU = new Edge();  //creating a new edge
            edgeFromU -> dst = ptrV;    //setting the destination which is v
            edgeFromU -> weight = 1; //setting the weight of the edge

            ptrU -> edgeList.push_back(edgeFromU);  //adding that edge to U's edge list 


        //now since this is an undirected graph we will also add the edge from v-> u
            for (int i=0; i < ptrV -> edgeList.size(); i++)
            {
                if (ptrV ->edgeList[i]->dst == ptrU) //edge already exists between v and u
                {
                    cerr<< "edge already exists" << endl;
                    return;
                }
            }
            //since there is not already an edge bw u and v we will add one 
            Edge * edgeFromV = new Edge();  //creating a new edge
            edgeFromV -> dst = ptrU;    //setting the destination which is U
            edgeFromV -> weight = 1; //setting the weight of the edge

            ptrV -> edgeList.push_back(edgeFromV);  //adding that edge to V's edge list 

        }
        
    }

}

void Graph::prettyPrint()   //function to print out the graph vertices and edges 
{
    cout << "---GRAPH------------------------------" << endl;
    for (int i = 0; i < vertexList.size(); ++i) //iterates over each vertex 
    {
        cout << vertexList[i]->name << "->";    //prints the name of the vertex
        for (int j = 0; j < vertexList[i]->edgeList.size(); j++)    //then iterates over the edge list 
        {
            cout << vertexList[i]->edgeList[j]->dst->name << ", "; //and prints the edges of that vertex
        }
        cout << endl;
    }
    cout << "--------------------------------------" << endl;
}

void Graph::depthFirstTraverseHelper(Vertex *p_u)
{
    // Recursive DFS 

    p_u -> visited = true; // Mark p_u as visited.
    cout << p_u-> name << " ";//prints all of the vertices in depth first fashion 

    for (int i =0; i < p_u->edgeList.size(); i++)   //iterate over all of p_u's outgoing edges
    {
        Vertex * p_v = p_u -> edgeList[i] -> dst;
        if (p_v -> visited ==false) //if it is not already visited 
        {
            depthFirstTraverseHelper(p_v);   //recursivly call this function again with that edge
        }
    }
}
void Graph::depthFirstTraverse(string s)    //function to print the function in depth first traversal style
{
    Vertex * source = getVertex(s); // Get a vertex* to the vertex named s

    if (source == 0) //check to see if vertex exists
    {
        cerr << "vertex" << s << "does not exist!" << endl; 
    }
    else    //otherwise it does exist
    {
        for (int i=0; i < vertexList.size(); i++)   //iterate over whole graph and set all vertices to not visited
        {
            vertexList[i] -> visited = false; 
        }
        cout << "Depth first traversal from" << s << endl;
        depthFirstTraverseHelper(source); // Call recursive DFS procedure 
        cout << endl;
    }
    
}

void Graph::breadthFirstTraverse(string s)
{
    queue<Vertex*> waitingq;  // Create a waiting queue 

    // mark s as visited and push it in the queue
    for (int i=0; i<vertexList.size(); i++)
    {
        vertexList[i]->visited= false;  //marking all vertexes as unvisited
    }   

    Vertex *ptr_s = getVertex(s); //poinnter to the vertex with the string s

    if (ptr_s == 0)   //vertex doesn't exist
    {
        cerr << "Vertex " << s << "not found " << endl;
        return;
    }

    else
    {
         ptr_s -> visited = true; //marking s as visited 
         waitingq.push(ptr_s); //pushing s onto the queue
    
        while (waitingq.empty() == false)
        {
            Vertex * ptr_u= waitingq.front(); 
            waitingq.pop();
            cout << ptr_u->name << " " ; 

            for (int i=0; i<ptr_u->edgeList.size(); i++)    //visiting all the adj vertexes of u 
            {
                Vertex *ptr_v= ptr_u -> edgeList[i] -> dst; //pointer to the vertex of the edge that we are visiting right now

                if (ptr_v->visited == false) 
                {
                    ptr_v->visited = true; //mark that edge as visited
                    waitingq.push(ptr_v); //then push it onto the queue 
                }
            }
        }
        
        cout << endl;
    
}
