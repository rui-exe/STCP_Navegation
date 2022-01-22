// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#include "graph.h"
#include <climits>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}


// ----------------------------------------------------------
// 1) Algoritmo de Dijkstra e caminhos mais curtos
// ----------------------------------------------------------




void Graph::dijkstra(int s) {
    for(int i=1;i<nodes.size();i++){
        nodes[i].dist = INT32_MAX;
        nodes[i].visited = false;
    }
    nodes[s].dist=0;
    nodes[s].pred = s;
    MinHeap<int,int> heap(nodes.size()-1,-1);
    for(int i=1;i<nodes.size();i++){
        heap.insert(i,nodes[i].dist);
    }
    while(heap.getSize()>0){
        int u = heap.removeMin();
        nodes[u].visited = true;
        for(Edge e:nodes[u].adj){
            int v = e.dest;
            if(!nodes[v].visited && nodes[u].dist+e.weight<nodes[v].dist) {
                nodes[v].dist = nodes[u].dist + e.weight;
                heap.decreaseKey(v, nodes[v].dist);
                nodes[v].pred = u;
            }

        }
    }
}

// ..............................
// a) Distância entre dois nós
// TODO
int Graph::dijkstra_distance(int a, int b) {
    dijkstra(a);
    return nodes[b].dist==INT32_MAX?-1:nodes[b].dist;
}

// ..............................
// b) Caminho mais curto entre dois nós
// TODO
list<int> Graph::dijkstra_path(int a, int b) {
    list<int> path;
    dijkstra(a);
    if(nodes[b].dist==INT32_MAX)
        return path;
    int dest = b;
    while(dest!=a){
        path.push_front(dest);
        dest=nodes[dest].pred;
    }
    path.push_front(dest);
    return path;
}
