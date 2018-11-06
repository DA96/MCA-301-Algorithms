//Section A
/*
Q2. From a given vertex in a weighted connected graph, find shortest paths to other
    vertices using Dijkstra's algorithm and bellman’s ford algorithm.
*/

//Author: Divya Agarwal

#include<iostream>
#include<climits>
#include<vector>
using namespace std;

#define NIL -1
#define V 5


int dist[V];
int parent[V];


void InitializeSingleSource(int source, int numV)
{
    for(int v = 0; v < numV; v++)
    {
        dist[v] = INT_MAX;
        parent[v] = NIL;
    }

    dist[source] = 0;
}

void relax(int u, int v, int weight)
{
    if(dist[v] > dist[u] + weight)
    {
        dist[v] = dist[u] + weight;
        parent[v] = u;
    }
}

int ExtractMin(bool setVertex[], int numV)
{
    int minDist = INT_MAX;
    int minDistVer;

    for(int v = 0; v < numV; v++)
    {
        if( !setVertex[v] && dist[v] < minDist )  // if vertex is not set i.e not processed
        {
            minDist = dist[v];
            minDistVer = v;
        }
    }
    return minDistVer;
}

void dijkstra(int graph[][V], int source, int numV)
{
    InitializeSingleSource(source, numV);

    bool setVertex[numV] = {0};

    for(int ctr = 0; ctr < numV-1; ctr++)
    {
        int u = ExtractMin(setVertex, numV);  // vertex with least distance
        setVertex[u] = 1;

        int weight;
        for(int v = 0; v < numV; v++)
        {
            if(graph[u][v]!=0) //means there exists an edge from u to v
            {
                weight = graph[u][v];
                relax(u,v,weight);

            }
        }
    }
}

bool bellmanFord(int graph[][V], int source, int numV)
{
     InitializeSingleSource(source, numV);

     int edges[numV*numV][3];

     int totalEdges=0;

     for(int u = 0; u < numV; u++)
        for(int v = 0; v < numV; v++)
            if(graph[u][v] != 0)
               {
                   edges[totalEdges][0] = u;
                   edges[totalEdges][1] = v;
                   edges[totalEdges][2] = graph[u][v];

                   totalEdges++;
               }


    for(int j = 0; j < numV-1; j++)
        for(int k=0; k < totalEdges; k++)
            relax(edges[k][0],edges[k][1],edges[k][2]);

    for(int k=0; k < totalEdges; k++)
        if(dist[edges[k][1]] > dist[edges[k][0]] + edges[k][2])
            return false;

    return true;
}


void printSolution(int numV)
{
   cout<<"Vertex    Distance from Source\n";
   for (int i = 0; i < numV; i++)
      cout<<" "<<i<<"\t\t"<<dist[i]<<endl;
}

int main()
{
    //example graph
    int graph[V][V] = {
                      {0, 10, 0, 5, 0},
                      {0, 0, 1, 2, 0},
                      {0, 0, 0, 0, 4},
                      {0, 3, 9, 0, 2},
                      {7, 0, 6, 0, 0},
                     };

    int graph2[V][V] = {
                      {0, 6, 0, 7, 0},
                      {0, 0, 5, 8, -4},
                      {0, -2, 0, 0, 0},
                      {0, 0, -3, 0, 9},
                      {-20, 0, 7, 0, 0},
                     };


    dijkstra(graph, 0, V);
    printSolution(V);

    if(bellmanFord(graph2, 0, V))
        printSolution(V);

    else cout<<"Negative edge cycle exists";



    return 0;
}
