// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "minHeap.h"
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <queue>
#include <limits>

using namespace std;

class Graph {

public:
    struct Edge {
        int dest;   // Destination node
        string line;
        long double weight; // A double weight
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        long double dist;
        int pred;
        bool visited;
        string code;
        string name;
        string zone;
        double latitude;
        double longitude;
        string line;
        int unweighted_distance;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented


    void dijkstra_less_changes(int s);
    void dijkstra_less_length(int s);

    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, string line,long double weight = 1);

    // ----- Functions to implement in this class -----
    long double dijkstra_less_length_distance(int a, int b);
    list<int> dijkstra_less_length_path(int a, int b);

    void bfs(int v);
    int unweighted_distance(int a, int b);

    list<int> unweighted_path(int a,int b);
};

#endif
