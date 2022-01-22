// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#include "graph.h"
#include <climits>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, string line,long double weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest,line, weight});
    if (!hasDir) nodes[dest].adj.push_back({src,line, weight});
}


// ----------------------------------------------------------
// 1) Algoritmo de Dijkstra e caminhos mais curtos
// ----------------------------------------------------------



void Graph::dijkstra_less_changes(int s) {
    for(int i=1;i<nodes.size();i++){
        nodes[i].dist = numeric_limits<long double>::max()/2;
        nodes[i].visited = false;
    }
    nodes[s].dist=0;
    nodes[s].pred = s;
    MinHeap<int,pair<long double,bool>> heap(nodes.size()-1,-1);
    for(int i=1;i<nodes.size();i++){
        heap.insert(i,{nodes[i].dist,true});
    }
    string current_line
    while(heap.getSize()>0){
        int u = heap.removeMin();
        nodes[u].visited = true;
        for(Edge e:nodes[u].adj){
            int v = e.dest;
            if(!nodes[v].visited && nodes[u].dist+e.weight<nodes[v].dist) {
                nodes[v].dist = nodes[u].dist + e.weight;
                heap.decreaseKey(v, nodes[v].dist);
                nodes[v].pred = u;
                nodes[v].line = e.line;
            }

        }
    }
}









void Graph::dijkstra_less_length(int s) {
    for(int i=1;i<nodes.size();i++){
        nodes[i].dist = numeric_limits<long double>::max()/2;
        nodes[i].visited = false;
    }
    nodes[s].dist=0;
    nodes[s].pred = s;
    MinHeap<int,long double> heap(nodes.size()-1,-1);
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
                nodes[v].line = e.line;
            }

        }
    }
}

// ..............................
// a) Distância entre dois nós
// TODO
long double Graph::dijkstra_less_length_distance(int a, int b) {
    dijkstra_less_length(a);
    return nodes[b].dist==(numeric_limits<long double>::max()/2)?-1:nodes[b].dist;
}

// ..............................
// b) Caminho mais curto entre dois nós
// TODO
list<int> Graph::dijkstra_less_length_path(int a, int b) {
    list<int> path;
    dijkstra_less_length(a);
    if(nodes[b].dist==(numeric_limits<long double>::max()/2))
        return path;
    int dest = b;
    while(dest!=a){
        path.push_front(dest);
        dest=nodes[dest].pred;
    }
    path.push_front(dest);
    return path;
}

void Graph::bfs(int v) {
    nodes[v].unweighted_distance=0;
    for (int i=1; i<=n; i++)
        nodes[i].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        for (const auto& e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].unweighted_distance = nodes[u].unweighted_distance+1;
                nodes[w].pred = u;
                nodes[w].line = e.line;
            }
        }
    }
}


int Graph::unweighted_distance(int a, int b){
    for(int i=1;i<=n;i++){
        nodes[i].unweighted_distance=0;
    }
    bfs(a);
    if(a!=b and nodes[b].unweighted_distance==0)
        return -1;
    else
        return nodes[b].unweighted_distance;
}

list<int> Graph::unweighted_path(int a,int b){
    list<int> path;
    bfs(a);
    if(!nodes[b].visited)
        return path;
    int dest = b;
    while(dest!=a){
        path.push_front(dest);
        dest=nodes[dest].pred;
    }
    path.push_front(dest);
    return path;
}