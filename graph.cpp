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

struct distance_zone_changes{
    inline distance_zone_changes(){
        this->distance = 0;
        this->changes = 0;
    }
    inline distance_zone_changes(distance_zone_changes const &d){
        this->distance = d.distance;
        this->changes = d.changes;
    }
    inline distance_zone_changes(long double distance,int changes){
        this->distance = distance;
        this->changes = changes;
    }
    long double distance;
    int changes;
    inline bool operator <(const distance_zone_changes &d) const{
        if(changes == d.changes)
            return distance<d.distance;
        else {
            return changes < d.changes;
        }
    }
    inline bool operator >(const distance_zone_changes &d) const{
        if(changes == d.changes)
            return distance>d.distance;
        else {
            return changes > d.changes;
        }
    }
};


void Graph::dijkstra_less_zones(int s) {
    for(int i=1;i<nodes.size();i++){
        nodes[i].dist = numeric_limits<long double>::max()/2;
        nodes[i].zones = numeric_limits<int>::max() / 2;
        nodes[i].visited = false;
        nodes[i].zones_used.clear();
    }
    nodes[s].dist=0;
    nodes[s].pred = s;
    nodes[s].zones=1;
    nodes[s].zones_used.insert(nodes[s].zone);
    MinHeap<int,distance_zone_changes> heap(nodes.size()-1,-1);
    for(int i=1;i<nodes.size();i++){
        heap.insert(i,distance_zone_changes(nodes[i].dist,nodes[i].zones));
    }
    while(heap.getSize()>0){
        int u = heap.removeMin();
        nodes[u].visited = true;
        for(const Edge& e:nodes[u].adj){
            int v = e.dest;
            if(!nodes[v].visited and (nodes[u].line!="walking" or e.line!="walking")) {
                int old_zone_changes = nodes[v].zones;
                int new_zone_changes;
                if (nodes[u].zones_used.find(nodes[v].zone)==nodes[u].zones_used.end()) {
                    new_zone_changes = nodes[u].zones_used.size()+1;
                }
                else
                    new_zone_changes = nodes[u].zones_used.size();
                if (new_zone_changes < old_zone_changes) {
                    nodes[v].zones_used = nodes[u].zones_used;
                    if(nodes[v].zones_used.find(nodes[v].zone)==nodes[v].zones_used.end())
                        nodes[v].zones_used.insert(nodes[v].zone);
                    nodes[v].zones = new_zone_changes;
                    nodes[v].dist = nodes[u].dist + e.weight;
                    heap.decreaseKey(v, distance_zone_changes(nodes[v].dist, nodes[v].zones));
                    nodes[v].pred = u;
                    nodes[v].line = e.line;
                }

                else if (nodes[v].zones == new_zone_changes and nodes[u].dist + e.weight < nodes[v].dist) {
                    nodes[v].zones_used = nodes[u].zones_used;
                    if(nodes[v].zones_used.find(nodes[v].zone)==nodes[v].zones_used.end())
                        nodes[v].zones_used.insert(nodes[v].zone);
                    nodes[v].dist = nodes[u].dist + e.weight;
                    heap.decreaseKey(v, distance_zone_changes(nodes[v].dist, nodes[v].zones));
                    nodes[v].pred = u;
                    nodes[v].line = e.line;
                }

            }
        }
    }
}



struct distance_changes{
    inline distance_changes(){
        this->distance = 0;
        this->changes = 0;
    }
    inline distance_changes(distance_changes const &d){
        this->distance = d.distance;
        this->changes = d.changes;
    }
    inline distance_changes(long double distance,int changes){
        this->distance = distance;
        this->changes = changes;
    }
    long double distance;
    int changes;
    inline bool operator <(const distance_changes &d) const{
        if(changes == d.changes)
            return distance<d.distance;
        else {
            return changes < d.changes;
        }
    }
    inline bool operator >(const distance_changes &d) const{
        if(changes == d.changes)
            return distance>d.distance;
        else {
            return changes > d.changes;
        }
    }
};

Graph Graph::stop_and_lines_graph(int a,int b) {
    Graph less_changes(0,true);
    unordered_map<string,int> name_to_int;
    name_to_int[nodes[b].code] = ++less_changes.n;
    less_changes.nodes.push_back(Node());
    less_changes.nodes[less_changes.n].code = nodes[b].code;
    for(int i=1;i<=n;i++){
        vector<string> lines_in_node;
        for(Edge e:nodes[i].adj){
            if(name_to_int.find(nodes[i].code+"-"+e.line)==name_to_int.end()) {
                name_to_int[nodes[i].code + "-" + e.line] = ++less_changes.n;
                less_changes.nodes.push_back(Node());
                less_changes.nodes[less_changes.n].code = nodes[i].code + "-" + e.line;
            }
            if(name_to_int.find(nodes[e.dest].code+"-"+e.line)==name_to_int.end()) {
                name_to_int[nodes[e.dest].code + "-" + e.line] = ++less_changes.n;
                less_changes.nodes.push_back(Node());
                less_changes.nodes[less_changes.n].code = nodes[e.dest].code + "-" + e.line;
            }
            less_changes.addEdge(name_to_int[nodes[i].code + "-" + e.line],name_to_int[nodes[e.dest].code + "-" + e.line],"",e.weight);
            lines_in_node.push_back(e.line);
            if(nodes[e.dest].code==nodes[b].code){
                less_changes.addEdge(name_to_int[nodes[i].code + "-" + e.line],name_to_int[nodes[b].code],"",0);
            }
        }
        for(int j=0;j<lines_in_node.size();j++){
            for(int k=j+1;k<lines_in_node.size();k++) {
                less_changes.addEdge(name_to_int[nodes[i].code +"-" +lines_in_node[j]],
                                     name_to_int[nodes[i].code + "-"+lines_in_node[k]], "", 1000);
                less_changes.addEdge(name_to_int[nodes[i].code + "-"+lines_in_node[k]],
                                     name_to_int[nodes[i].code + "-"+lines_in_node[j]], "", 1000);
            }
        }
    }
    less_changes.n++;
    less_changes.nodes.push_back(Node());
    less_changes.nodes[less_changes.n].code = nodes[a].code;
    for(Edge e:nodes[a].adj){
        less_changes.addEdge(less_changes.n,name_to_int[nodes[a].code+"-"+e.line],"",0);
    }
    return less_changes;
}



list<int> Graph::dijkstra_less_zones_path(int a, int b){
    list<int> path;
    dijkstra_less_zones(a);
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

pair<string,string> split(string word,char delim){
    pair<string,string> answer;
    string aux;
    for(char c:word){
        if(c==delim) {
            answer.first=aux;
            aux = "";
        }
        else
            aux+=c;
    }
    if(answer.first=="")
        answer.first=aux;
    else
        answer.second=aux;
    return answer;
}

list<int> Graph::dijkstra_less_changes_path(int a,int b,unordered_map<string,int> code_to_node){
    Graph stop_and_lines = stop_and_lines_graph(a,b);
    stop_and_lines.dijkstra_less_length(stop_and_lines.n);
    list<int> path;
    if(stop_and_lines.nodes[1].dist==(numeric_limits<long double>::max()/2))
        return path;
    int dest = 1;
    while(dest!=stop_and_lines.n){
        pair<string,string> stop_line = split(stop_and_lines.nodes[dest].code,'-');
        path.push_front(code_to_node[stop_line.first]);
        nodes[code_to_node[stop_line.first]].line=stop_line.second;
        dest=stop_and_lines.nodes[dest].pred;
    }
    pair<string,string> stop_line = split(stop_and_lines.nodes[dest].code,'-');
    path.push_front(code_to_node[stop_line.first]);
    nodes[code_to_node[stop_line.first]].line=stop_line.second;
    return path;
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
            if(!nodes[v].visited and nodes[u].dist+e.weight<nodes[v].dist and (nodes[u].line!="walking" or e.line!="walking")) {
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
            if (!nodes[w].visited and (nodes[u].line!="walking" or e.line!="walking")) {
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

long double toRadians(const long double degree)
{
// cmath library in C++
// defines the constant
// M_PI as the value of
// pi accurate to 1e-30
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1,
                     long double lat2, long double long2)
{
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
                      cos(lat1) * cos(lat2) *
                      pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 6371;

    // Calculate the result
    ans = ans * R;

    return ans;
}

Graph Graph::add_walking(long double dist) {
    Graph walking_graph = *this;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if ((dist_stops(walking_graph.nodes[i], walking_graph.nodes[j]) < dist) and i!=j)
                walking_graph.addEdge(i, j, "walking"), dist_stops(nodes[i], nodes[j]);
        }
    }
    return walking_graph;
}

Graph Graph::add_location(double latitude,double longitude){
    Graph a_to_station = * this;
    a_to_station.n++;
    a_to_station.nodes.push_back(Node());
    a_to_station.nodes[a_to_station.n].name = "Local inicial";
    a_to_station.nodes[a_to_station.n].latitude = latitude;
    a_to_station.nodes[a_to_station.n].longitude = longitude;
    return a_to_station;
}


long double Graph::dist_stops(const Node& previous_node,const Node& current_node){
    return distance(previous_node.latitude,previous_node.longitude,
                  current_node.latitude,current_node.longitude);
}