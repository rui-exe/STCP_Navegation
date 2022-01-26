// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#include "graph.h"
#include <climits>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, string line,long double weight,bool changes) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest,line, weight,changes});
    if (!hasDir) nodes[dest].adj.push_back({src,line, weight,changes});
}

// ----------------------------------------------------------
// 1) Algoritmo de Dijkstra e caminhos mais curtos
// ----------------------------------------------------------

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


void Graph::dijkstra_less_zones(int s) {
    for(int i=1;i<nodes.size();i++){
        nodes[i].zones = numeric_limits<int>::max() / 2;
        nodes[i].line_changes = numeric_limits<int>::max() / 2;
        nodes[i].visited = nodes[i].closed;
        nodes[i].zones_used.clear();
    }
    nodes[s].pred = s;
    nodes[s].zones=1;
    nodes[s].zones_used.insert(nodes[s].zone);
    MinHeap<int,zones_line_changes> heap(nodes.size()-1,-1);
    for(int i=1;i<nodes.size();i++){
        heap.insert(i,{nodes[i].line_changes,nodes[i].zones});
    }
    while(heap.getSize()>0){
        int u = heap.removeMin();
        nodes[u].visited = true;
        for(Edge e:nodes[u].adj){
            int v = e.dest;
            if(!nodes[v].visited) {
                int old_zone_changes = nodes[v].zones;
                int new_zone_changes;
                if (nodes[u].zones_used.find(nodes[v].zone)==nodes[u].zones_used.end()) {
                    new_zone_changes = nodes[u].zones_used.size()+1;
                }
                else
                    new_zone_changes = nodes[u].zones_used.size();
                if (new_zone_changes < old_zone_changes) {
                    if (split(nodes[u].code, '-').second != "walking" or
                        split(nodes[v].code, '-').second != "walking") {
                        nodes[v].zones_used = nodes[u].zones_used;
                        if (nodes[v].zones_used.find(nodes[v].zone) == nodes[v].zones_used.end())
                            nodes[v].zones_used.insert(nodes[v].zone);
                        nodes[v].line_changes = nodes[u].line_changes + e.changes;
                        nodes[v].zones = new_zone_changes;
                        heap.decreaseKey(v, {nodes[v].line_changes, nodes[v].zones});
                        nodes[v].pred = u;
                        if (split(nodes[u].code, '-').second == "walking")
                            nodes[v].line = "walking";
                    } else if (nodes[u].line != "walking") {
                        nodes[v].zones_used = nodes[u].zones_used;
                        if (nodes[v].zones_used.find(nodes[v].zone) == nodes[v].zones_used.end())
                            nodes[v].zones_used.insert(nodes[v].zone);
                        nodes[v].line_changes = nodes[u].line_changes + e.changes;
                        nodes[v].zones = new_zone_changes;
                        heap.decreaseKey(v, {nodes[v].line_changes, nodes[v].zones});
                        nodes[v].pred = u;
                        nodes[v].line = "walking";
                    }
                }
                else if (new_zone_changes == old_zone_changes and
                         nodes[u].line_changes + e.changes< nodes[v].line_changes) {
                    if (split(nodes[u].code, '-').second != "walking" or
                        split(nodes[v].code, '-').second != "walking") {
                        nodes[v].zones_used = nodes[u].zones_used;
                        if(nodes[v].zones_used.find(nodes[v].zone)==nodes[v].zones_used.end())
                            nodes[v].zones_used.insert(nodes[v].zone);
                        nodes[v].line_changes = nodes[u].line_changes + e.changes;
                        nodes[v].zones = new_zone_changes;
                        heap.decreaseKey(v, {nodes[v].line_changes, nodes[v].zones});
                        nodes[v].pred = u;
                        if (split(nodes[u].code, '-').second == "walking")
                            nodes[v].line = "walking";
                    } else if (nodes[u].line != "walking") {
                        nodes[v].zones_used = nodes[u].zones_used;
                        if(nodes[v].zones_used.find(nodes[v].zone)==nodes[v].zones_used.end())
                            nodes[v].zones_used.insert(nodes[v].zone);
                        nodes[v].line_changes = nodes[u].line_changes + e.changes;
                        nodes[v].zones = new_zone_changes;
                        heap.decreaseKey(v, {nodes[v].line_changes, nodes[v].zones});
                        nodes[v].pred = u;
                        nodes[v].line = "walking";
                    }
                }
            }
        }
    }
}


Graph Graph::stop_and_lines_graph(int a,int b) {
    bool line_walking=false;
    Graph less_changes(0,true);
    unordered_map<string,int> name_to_int;
    name_to_int[nodes[b].code] = ++less_changes.n;
    less_changes.nodes.push_back(Node());
    less_changes.nodes[less_changes.n].code = nodes[b].code;
    less_changes.nodes[less_changes.n].zone = nodes[b].zone;
    less_changes.nodes[less_changes.n].closed = nodes[b].closed;
    for(int i=1;i<=n;i++){
        unordered_set<string> set_lines_in_node;
        vector<string> lines_in_node;
        for(Edge e:nodes[i].adj){
            if(name_to_int.find(nodes[i].code+"-"+e.line)==name_to_int.end()) {
                name_to_int[nodes[i].code + "-" + e.line] = ++less_changes.n;
                less_changes.nodes.push_back(Node());
                less_changes.nodes[less_changes.n].code = nodes[i].code + "-" + e.line;
                less_changes.nodes[less_changes.n].zone = nodes[i].zone;
                less_changes.nodes[less_changes.n].closed = nodes[i].closed;
            }
            if(name_to_int.find(nodes[e.dest].code+"-"+e.line)==name_to_int.end()) {
                name_to_int[nodes[e.dest].code + "-" + e.line] = ++less_changes.n;
                less_changes.nodes.push_back(Node());
                less_changes.nodes[less_changes.n].code = nodes[e.dest].code + "-" + e.line;
                less_changes.nodes[less_changes.n].zone = nodes[e.dest].zone;
                less_changes.nodes[less_changes.n].closed = nodes[e.dest].closed;
            }
            less_changes.addEdge(name_to_int[nodes[i].code + "-" + e.line],name_to_int[nodes[e.dest].code + "-" + e.line],"",
                                 e.weight,false);
            set_lines_in_node.insert(e.line);
            if(nodes[e.dest].code==nodes[b].code){ //edges from b-linex to b, not repeating b-walking
                if(!line_walking and e.line=="walking") {
                    less_changes.addEdge(name_to_int[nodes[b].code + "-" + e.line], name_to_int[nodes[b].code], "",0,false);
                    line_walking = true;
                }
                else if(e.line!="walking")
                    less_changes.addEdge(name_to_int[nodes[b].code + "-" + e.line], name_to_int[nodes[b].code], "",0,false);
            }
        }

        while(!set_lines_in_node.empty()){
            lines_in_node.push_back(*set_lines_in_node.begin());
            set_lines_in_node.erase(set_lines_in_node.begin());
        }
        for(int j=0;j<lines_in_node.size();j++){ //nodes to change line, 0 changes if changing to a walking line, that change is considered when changing back to
            for(int k=j+1;k<lines_in_node.size();k++) {  //a regular line
                if (lines_in_node[k] == "walking") {
                    less_changes.addEdge(name_to_int[nodes[i].code + "-" + lines_in_node[j]],
                                         name_to_int[nodes[i].code + "-" + lines_in_node[k]], "",0,false);
                }
                else {
                less_changes.addEdge(name_to_int[nodes[i].code + "-" + lines_in_node[j]],
                                     name_to_int[nodes[i].code + "-" + lines_in_node[k]], "",0,true);
                }
                less_changes.addEdge(name_to_int[nodes[i].code + "-"+lines_in_node[k]],
                                     name_to_int[nodes[i].code + "-"+lines_in_node[j]], "",0,true);
            }
        }
    }
    less_changes.n++;
    less_changes.nodes.push_back(Node());
    less_changes.nodes[less_changes.n].code = nodes[a].code;
    less_changes.nodes[less_changes.n].zone = nodes[a].zone;
    less_changes.nodes[less_changes.n].closed = nodes[a].closed;
    line_walking=false;
    for(Edge e:nodes[a].adj){ //edges from a to a-linex ,not repeating a-walking
        if(!line_walking and e.line=="walking") {
            less_changes.addEdge(less_changes.n, name_to_int[nodes[a].code + "-" + e.line], "",0,false);
            line_walking = true;
        }
        else if(e.line!="walking")
            less_changes.addEdge(less_changes.n, name_to_int[nodes[a].code + "-" + e.line], "",0,false);
    }
    return less_changes;
}



list<int> Graph::dijkstra_less_zones_path(int a, int b, unordered_map<string,int> code_to_node){
    Graph stop_and_lines = stop_and_lines_graph(a,b);
    stop_and_lines.dijkstra_less_zones(stop_and_lines.n);
    list<int> path;
    if(stop_and_lines.nodes[1].dist==(numeric_limits<long double>::max()/2))
        return path;
    int dest = 1;
    string previous_station;
    while(dest!=stop_and_lines.n){
        pair<string,string> stop_line = split(stop_and_lines.nodes[dest].code,'-');
        if(previous_station!=stop_line.first) {
            previous_station = stop_line.first;
            path.push_front(code_to_node[stop_line.first]);
            nodes[code_to_node[stop_line.first]].line = stop_line.second;
        }
        dest = stop_and_lines.nodes[dest].pred;
    }
    return path;
}

void Graph::dijkstra_less_changes(int s){
    for(int i=1;i<nodes.size();i++){
        nodes[i].dist = numeric_limits<long double>::max()/2;
        nodes[i].line_changes = numeric_limits<int>::max()/2;
        nodes[i].visited = nodes[i].closed;
    }
    nodes[s].dist=0;
    nodes[s].line_changes = 0;
    nodes[s].pred = s;
    MinHeap<int,changes_dist> heap(nodes.size()-1,-1);
    for(int i=1;i<nodes.size();i++){
        heap.insert(i,{nodes[i].dist,nodes[i].line_changes});
    }
    while(heap.getSize()>0){
        int u = heap.removeMin();
        nodes[u].visited = true;
        for(Edge e:nodes[u].adj){
            int v = e.dest;
            if(!nodes[v].visited) {
                if (nodes[u].line_changes + e.changes < nodes[v].line_changes) {
                    if (split(nodes[u].code, '-').second != "walking" or
                        split(nodes[v].code, '-').second != "walking") {
                        nodes[v].line_changes = nodes[u].line_changes + e.changes;
                        nodes[v].dist = nodes[u].dist + e.weight;
                        heap.decreaseKey(v, {nodes[v].dist, nodes[v].line_changes});
                        nodes[v].pred = u;
                        if (split(nodes[u].code, '-').second == "walking")
                            nodes[v].line = "walking";
                    } else if (nodes[u].line != "walking") {
                        nodes[v].line_changes = nodes[u].line_changes + e.changes;
                        nodes[v].dist = nodes[u].dist + e.weight;
                        heap.decreaseKey(v, {nodes[v].dist, nodes[v].line_changes});
                        nodes[v].pred = u;
                        nodes[v].line = "walking";
                    }
                }
                else if (nodes[u].line_changes + e.changes == nodes[v].line_changes and
                            nodes[u].dist + e.weight< nodes[v].dist) {
                    if (split(nodes[u].code, '-').second != "walking" or
                        split(nodes[v].code, '-').second != "walking") {
                        nodes[v].dist = nodes[u].dist + e.weight;
                        heap.decreaseKey(v, {nodes[v].dist, nodes[v].line_changes});
                        nodes[v].pred = u;
                        if (split(nodes[u].code, '-').second == "walking")
                            nodes[v].line = "walking";
                    } else if (nodes[u].line != "walking") {
                        nodes[v].dist = nodes[u].dist + e.weight;
                        heap.decreaseKey(v, {nodes[v].dist, nodes[v].line_changes});
                        nodes[v].pred = u;
                        nodes[v].line = "walking";
                    }
                }
            }
        }
    }
}

list<int> Graph::dijkstra_less_changes_path(int a,int b,unordered_map<string,int> code_to_node){
    Graph stop_and_lines = stop_and_lines_graph(a,b);
    stop_and_lines.dijkstra_less_changes(stop_and_lines.n);
    list<int> path;
    if(stop_and_lines.nodes[1].dist==(numeric_limits<long double>::max()/2))
        return path;
    int dest = 1;
    string previous_station;
    while(dest!=stop_and_lines.n){
        pair<string,string> stop_line = split(stop_and_lines.nodes[dest].code,'-');
        if(previous_station!=stop_line.first) {
            previous_station = stop_line.first;
            path.push_front(code_to_node[stop_line.first]);
            nodes[code_to_node[stop_line.first]].line = stop_line.second;
            nodes[code_to_node[stop_line.first]].dist = stop_and_lines.nodes[dest].dist;
        }
        dest = stop_and_lines.nodes[dest].pred;
    }
    return path;
}




void Graph::dijkstra_less_length(int s) {
    for(int i=1;i<nodes.size();i++){
        nodes[i].dist = numeric_limits<long double>::max()/2;
        nodes[i].line_changes = numeric_limits<int>::max()/2;
        nodes[i].visited = nodes[i].closed;
    }
    nodes[s].dist=0;
    nodes[s].line_changes = 0;
    nodes[s].pred = s;
    MinHeap<int,distance_changes> heap(nodes.size()-1,-1);
    for(int i=1;i<nodes.size();i++){
        heap.insert(i,{nodes[i].dist,nodes[i].line_changes});
    }
    while(heap.getSize()>0){
        int u = heap.removeMin();
        nodes[u].visited = true;
        for(Edge e:nodes[u].adj){
            int v = e.dest;
            if(!nodes[v].visited) {
                if (nodes[u].dist + e.weight < nodes[v].dist) {
                    if (split(nodes[u].code, '-').second != "walking" or
                        split(nodes[v].code, '-').second != "walking") {
                        nodes[v].line_changes = nodes[u].line_changes + e.changes;
                        nodes[v].dist = nodes[u].dist + e.weight;
                        heap.decreaseKey(v, {nodes[v].dist, nodes[v].line_changes});
                        nodes[v].pred = u;
                        if (split(nodes[u].code, '-').second == "walking")
                            nodes[v].line = "walking";
                    } else if (nodes[u].line != "walking") {
                        nodes[v].line_changes = nodes[u].line_changes + e.changes;
                        nodes[v].dist = nodes[u].dist + e.weight;
                        heap.decreaseKey(v, {nodes[v].dist, nodes[v].line_changes});
                        nodes[v].pred = u;
                        nodes[v].line = "walking";
                    }
                }
                else if (nodes[u].dist + e.weight == nodes[v].dist and
                         nodes[u].line_changes + e.changes< nodes[v].line_changes) {
                    if (split(nodes[u].code, '-').second != "walking" or
                        split(nodes[v].code, '-').second != "walking") {
                        nodes[v].line_changes = nodes[u].line_changes + e.changes;
                        heap.decreaseKey(v, {nodes[v].dist, nodes[v].line_changes});
                        nodes[v].pred = u;
                        if (split(nodes[u].code, '-').second == "walking")
                            nodes[v].line = "walking";
                    } else if (nodes[u].line != "walking") {
                        nodes[v].line_changes = nodes[u].line_changes + e.changes;
                        heap.decreaseKey(v, {nodes[v].dist, nodes[v].line_changes});
                        nodes[v].pred = u;
                        nodes[v].line = "walking";
                    }
                }
            }
        }
    }
}

list<int> Graph::dijkstra_less_length_path(int a, int b,unordered_map<string,int> code_to_node) {
    Graph stop_and_lines = stop_and_lines_graph(a,b);
    stop_and_lines.dijkstra_less_length(stop_and_lines.n);
    list<int> path;
    if(stop_and_lines.nodes[1].dist==(numeric_limits<long double>::max()/2))
        return path;
    int dest = 1;
    string previous_station;
    while(dest!=stop_and_lines.n){
        pair<string,string> stop_line = split(stop_and_lines.nodes[dest].code,'-');
        if(previous_station!=stop_line.first) {
            previous_station = stop_line.first;
            path.push_front(code_to_node[stop_line.first]);
            nodes[code_to_node[stop_line.first]].line = stop_line.second;
            nodes[code_to_node[stop_line.first]].dist = stop_and_lines.nodes[dest].dist;
        }
        dest = stop_and_lines.nodes[dest].pred;
    }
    return path;
}

void Graph::bfs(int v) {
    nodes[v].unweighted_distance=0;
    for (int i=1; i<=n; i++)
        nodes[i].visited = nodes[i].closed;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
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

void Graph::add_walking(long double dist) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if ((dist_stops(nodes[i], nodes[j]) < dist) and i!=j)
                this->addEdge(i, j, "walking", dist_stops(nodes[i], nodes[j]));
        }
    }
}

void Graph::add_initial_location(double latitude,double longitude, long double walking_dist){
    this->n++;
    nodes.push_back(Node());
    nodes[n].name = "Local inicial";
    nodes[n].code = "LI";
    nodes[n].latitude = latitude;
    nodes[n].longitude = longitude;
    nodes[n].closed = false;
    for(int i=1;i<n;i++){
        if (dist_stops(nodes[n], nodes[i]) < walking_dist) {
            this->addEdge(i, n, "walking", dist_stops(nodes[i], nodes[n]));
            this->addEdge(n, i, "walking", dist_stops(nodes[i], nodes[n]));
        }
    }
}

void Graph::add_final_location(double latitude,double longitude, long double walking_dist){
    this->n++;
    nodes.push_back(Node());
    nodes[n].name = "Local final";
    nodes[n].code = "LF";
    nodes[n].latitude = latitude;
    nodes[n].longitude = longitude;
    nodes[n].closed = false;
    for(int i=1;i<n;i++){
        if (dist_stops(nodes[n], nodes[i]) < walking_dist) {
            this->addEdge(i, n, "walking", dist_stops(nodes[i], nodes[n]));
            this->addEdge(n, i, "walking", dist_stops(nodes[i], nodes[n]));
        }
    }
}

long double Graph::dist_stops(const Node& previous_node,const Node& current_node){
    return distance(previous_node.latitude,previous_node.longitude,
                                    current_node.latitude,current_node.longitude);
}