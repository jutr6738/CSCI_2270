#include <iostream>
#include "Graph.hpp"
#include <vector> // for vertex and edge lists
#include <queue>  // for breadth first traversal

using namespace std;

Vertex * Graph::getVertex(string u)
{
    // Given a vertex name return the vertex pointer to the vertex 

    for (int i =0; i < vertexList.size(); ++i) {
        if (vertexList[i]->name == u) return vertexList[i];        
    }

    return 0;
}

void Graph::addVertex(string u)
{
    // If vertex with the same name is not in the graph, add  vertex
    if (getVertex(u) == 0) {
        Vertex* tmp = new Vertex();
        tmp->name = u;
        tmp->visited = false;
        tmp->distance = -1;

        vertexList.push_back(tmp);
    } 
    else {
        cerr << " vertex " << u << " already exists" << endl;
    }

    return;
}

void Graph::addEdge(string u, string v)
{
    // If u = v, ignore ...
    if (u == v) return;
    else {
        Vertex* p_u = getVertex(u);
        Vertex* p_v = getVertex(v);
        
        if (p_u == 0 || p_v == 0) {
            cerr << " One of the vertices is not in the graph" << endl;
            return;
        }
        else {
            // adding an edge from u-> v
            for (int i = 0; i < p_u->edgeList.size(); ++i) {
                if (p_u->edgeList[i]->dst == p_v) {
                    cerr << " edge already exists" << endl;
                    return;
                }
            }

            Edge* e_u = new Edge();
            e_u->dst = p_v;
            e_u->weight = 1;
            
            p_u->edgeList.push_back(e_u);


            // add an edge from v-> u 
            for (int i = 0; i < p_v->edgeList.size(); ++i) {
                if (p_v->edgeList[i]->dst == p_u) {
                    cerr << " edge already exists" << endl;
                    return;
                }
            }

            Edge* e_v = new Edge();
            e_v->dst = p_u;
            e_v->weight = 1;
            
            p_v->edgeList.push_back(e_v);



        }

    }
}
void Graph::addEdge(string u, string v, int w)
{
    // If u = v, ignore ...
    if (u == v) return;
    else {
        Vertex* p_u = getVertex(u);
        Vertex* p_v = getVertex(v);
        
        if (p_u == 0 || p_v == 0) {
            cerr << " One of the vertices is not in the graph" << endl;
            return;
        }
        else {
            // adding an edge from u-> v
            for (int i = 0; i < p_u->edgeList.size(); ++i) {
                if (p_u->edgeList[i]->dst == p_v) {
                    cerr << " edge already exists" << endl;
                    return;
                }
            }

            Edge* e_u = new Edge();
            e_u->dst = p_v;
            e_u->weight = w;
            
            p_u->edgeList.push_back(e_u);


            // add an edge from v-> u 
            for (int i = 0; i < p_v->edgeList.size(); ++i) {
                if (p_v->edgeList[i]->dst == p_u) {
                    cerr << " edge already exists" << endl;
                    return;
                }
            }

            Edge* e_v = new Edge();
            e_v->dst = p_u;
            e_v->weight = w;
            
            p_v->edgeList.push_back(e_v);



        }

    }
}

void Graph::prettyPrint()
{
    cout << "---GRAPH------------------------------" << endl;
    for (int i = 0; i < vertexList.size(); ++i)
    {
        cout << vertexList[i]->name << "->";
        for (int j = 0; j < vertexList[i]->edgeList.size(); j++)
        {
            cout << vertexList[i]->edgeList[j]->dst->name << "(" << vertexList[i]->edgeList[j]->weight<< ")" << ", ";
        }
        cout << endl;
    }
    cout << "--------------------------------------" << endl;
}

void Graph::depthFirstTraverseHelper(Vertex *p_u)
{
    p_u->visited = true;
    cout << p_u->name << " ";
    for (int i = 0; i < p_u->edgeList.size(); ++i) {
        Vertex* p_v = p_u->edgeList[i]->dst;
        if (!p_v->visited) depthFirstTraverseHelper(p_v);
    }
}

void Graph::depthFirstTraverse(string s)
{
    // Get a vertex* to the vertex named s
    Vertex* p_s = getVertex(s);

    if (p_s == 0) {
        cerr << " vertex " << s << "  does not exist!" << endl;
    }
    else {
        for (int i = 0; i < vertexList.size(); ++i) vertexList[i]->visited = false;

        cout << " Depth first traversal from " << s << endl;
        depthFirstTraverseHelper(p_s);
        cout << endl;

    }
    // Mark every vertex visited 
    // Call recursive DFS procedure 
}

void Graph::breadthFirstTraverse(string s)
{
  queue<Vertex*> waiting;

  for (int i = 0 ; i < vertexList.size(); ++i) {
      vertexList[i]->visited = false;
  }

  Vertex* p_s = getVertex(s);

  if (p_s == 0) {
      cerr << "Vertex " << s << " not found " << endl;
      return;
  }
  else {
      p_s->visited = true;
      p_s->distance = 0;
      waiting.push(p_s); 

       while (!waiting.empty()) {
           Vertex* p_u = waiting.front();
           int d = p_u->distance;
           waiting.pop();
           cout << p_u->name << " ";

            for (int i = 0; i < p_u->edgeList.size(); i++) {
                Vertex* p_v = p_u->edgeList[i]->dst;

                if (!p_v->visited) {
                    p_v->visited = true;
                    p_v->distance = d + 1;
                    waiting.push(p_v);
                }
            }
       } 
       cout << endl;
  }
    // Create a waiting queue 
    // mark s as visited and push it in the queue

    // while queue is not empty 
        // pop the queue, visit the popped vertex  
        // push all of the unvisited vertices to the queue 

}

void Graph::printDistance() {
    for (int i = 0; i < vertexList.size(); ++i) {
        cout << "dist("<< vertexList[i]->name << ") = " << vertexList[i]->distance << endl;
    }
}

void Graph::clearDisance() {
    for (int i = 0; i < vertexList.size(); ++i) {
        vertexList[i]->distance = -1;
    }
}

void Graph::dijkstraTraverse(string s) {
    Vertex* p_s = getVertex(s);

  if (p_s == 0) {
      cerr << "Vertex " << s << " not found " << endl;
      return;
  }
  else {
      /* Implement Dijsktra Algorithm */
      for (int i=0; i< vertexList.size(); i++)
      {
          vertexList[i]->distance = INT8_MAX;    //initializing all distance to something huge
          vertexList[i] -> prev= 0; //initializing all previous vertexs as nothing 
          vertexList[i]-> visited = false; //initializing all as unvisited
      }

      p_s-> distance =0;    //make our start vertex distance 0
      p_s->visited= true; //make our start vertex as visited

      vector<Vertex*> solvedList;   //vector of vertex pointers that wwill hold the vertexes where we already know the distance to them
      solvedList.push_back(p_s); 

      bool solved =false;

      while (!solved) //will run until we have all the distances of all of the nodes //iterating through all the nodes in the solved list until we find the minimum distance 
      {
          int minDist = INT8_MAX;
          Vertex * minVertex= 0;
          solved = true; 

          for (int i = 0; i < solvedList.size(); i++)   //looking at everthing in the solved list and looking at each of the distances 
          {
              Vertex * currinsolvedlist = solvedList[i];
              for (int j=0; j< currinsolvedlist->edgeList.size(); j++)
              {
                  Vertex * someedgeofcurr= currinsolvedlist-> edgeList[j]->dst; 
                  int w= currinsolvedlist-> edgeList[j]->weight; 
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
}