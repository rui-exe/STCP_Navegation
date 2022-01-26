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
#include <algorithm>
#include <unordered_set>
#include <cmath>
#include <set>

using namespace std;

class Graph {

public:
    /**
    * A struct that basically serves our notion of distance between the graph's nodes.
    * This one prioritizes less zones used and then prioritizes less bus changes.
    */
    struct zones_line_changes{
        inline zones_line_changes(){
            this->line_changes = 0;
            this->zone_changes = 0;
        }
        inline zones_line_changes(zones_line_changes const &d){
            this->line_changes = d.line_changes;
            this->zone_changes = d.zone_changes;
        }
        inline zones_line_changes(int line_changes,int zone_changes){
            this->line_changes = line_changes;
            this->zone_changes = zone_changes;
        }
        int line_changes;
        int zone_changes;
        inline bool operator <(const zones_line_changes &d) const{
            if(zone_changes == d.zone_changes)
                return line_changes<d.line_changes;
            else {
                return zone_changes < d.zone_changes;
            }
        }
        inline bool operator >(const zones_line_changes &d) const{
            if(zone_changes == d.zone_changes)
                return line_changes>d.line_changes;
            else {
                return zone_changes > d.zone_changes;
            }
        }
    };
    /**
     * A struct that basically serves our notion of distance between the graph's nodes.
     * This one prioritizes less bus line changes and then prioritizes the distance traveled.
     */
    struct changes_dist{
        inline changes_dist(){
            this->distance = 0;
            this->changes = 0;
        }
        inline changes_dist(changes_dist const &d){
            this->distance = d.distance;
            this->changes = d.changes;
        }
        inline changes_dist(long double distance,int changes){
            this->distance = distance;
            this->changes = changes;
        }
        long double distance;
        int changes;
        inline bool operator <(const changes_dist &d) const{
            if(changes == d.changes)
                return distance<d.distance;
            else {
                return changes < d.changes;
            }
        }
        inline bool operator >(const changes_dist &d) const{
            if(changes == d.changes)
                return distance>d.distance;
            else {
                return changes > d.changes;
            }
        }
    };
    /**
     * A struct that basically serves our notion of distance between the graph's nodes.
     * This one prioritizes less distance traveled and then prioritizes less bus line changes.
     */
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
            if(distance == d.distance)
                return changes<d.changes;
            else {
                return distance < d.distance;
            }
        }
        inline bool operator >(const distance_changes &d) const{
            if(distance == d.distance)
                return changes>d.changes;
            else {
                return distance > d.distance;
            }
        }
    };

    struct Edge {
        int dest;   // Destination node
        string line;
        long double weight; // A double weight
        bool changes;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        long double dist;
        int pred;
        int line_changes;
        int zones;
        bool visited;
        string code;
        string name;
        string zone;
        double latitude;
        double longitude;
        string line;
        int unweighted_distance;
        unordered_set<string> zones_used;
        bool closed;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

    /**
     *
     * @param source
     * @param destination
     * @return A graph with nodes representing each line+station,with edges between nodes of the same lines and connecting all nodes representing the same station to
     * each other. This edges have 0 distance as they are in the same station, but they count as a change in lines. The edges from some line to a walking line
     * don't count as a change as that change will be considered when changing back from a walking line to a regular line.
     * There is also a node source which only represents the source station (without any line) and has edges from it to all the other nodes representing
     * the same station and it's corresponding lines, and a node destination which only represents the destination station (without any line) and has edges from
     * the other nodes representing the same station and it's corresponding lines to it.
     * Complexity: O(n) = V*(E(V)^2)     (E(V)= Edges in each node)
     */

    Graph stop_and_lines_graph(int a,int b);
    /**
     * Calculates the distance in kilometers to every node of the graph starting on the start node s
     * @param s int representing the node in which we want to start and calculate the distance to the other nodes
     * Complexity O(n)= Elog|V| where E is the number of edges and V the number of vertices
     */
    void dijkstra_less_length(int s);
    /**
     * Calculates the distance in terms of less number of zones used to every node of the graph starting on the start node s
     * @param s int representing the node in which we want to start and calculate the distance to the other nodes
     * Complexity O(n)= Elog|V| where E is the number of edges and V the number of vertices
     */
    void dijkstra_less_zones(int s);
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, string line,long double weight = 1,bool changes=false);
    /**
     * Function that invokes the dijkstra_less_lenght() and returns the best path
     * from node a to node b in terms of kilometers traveled.
     * @param a int representing the starting node we want to calculate the best path from
     * @param b int representing the final node we want to calculate the best path to
     * @param code_to_node unordered_map so we can map the station's code to the int representing the node on the graph
     * @return list of integers that represent the best path from node a to node b
     */
    list<int> dijkstra_less_length_path(int a, int b,unordered_map<string,int> code_to_node);
    /**
     * Function that invokes the dijkstra_less_changes() and returns the best path
     * from node a to b in terms of less bus changes made.
     * @param a int representing the starting node we want to calculate the best path from
     * @param b int representing the final node we want to calculate the best path to
     * @param code_to_node unordered_map so we can map the station's code to the int representing the node on the graph
     * @return list of integers that represent the best path from node a to node b
     */
    list<int> dijkstra_less_changes_path(int a, int b,unordered_map<string,int> code_to_node);
    /**
     * Function that invokes the dijkstra_less_zones() and returns the best path
     * from node a to b in terms of less zones used.
     * @param a int representing the starting node we want to calculate the best path from
     * @param b int representing the final node we want to calculate the best path to
     * @param code_to_node unordered_map so we can map the station's code to the int representing the node on the graph
     * @return list of integers that represent the best path from node a to node b
     */
    list<int> dijkstra_less_zones_path(int a, int b,unordered_map<string,int> code_to_node);
    /**
     * Function that calculates the distance in kilometers between two nodes of the graph
     * @param previous_node int that represents node a
     * @param current_node int that represents node b
     * @return long double representing the distance in kilometers between node a and node b.
     */
    static long double dist_stops(const Node& previous_node,const Node& current_node);
    void bfs(int v);
    void add_walking(long double dist);
    /**
     * Function that adds an extra node to the graph which is an initial location specified by the user.
     * @param latitude latitude coordinates of the initial specified location
     * @param longitude longitude coordinates of the inital specified location
     * @param walking_dist distance user can walk
     */
    void add_initial_location(double latitude,double longitude,long double walking_dist);
    /**
     * Function that adds an extra node to the graph which is a final location specified by the user.
     * @param latitude latitude coordinates of the final specified location
     * @param longitude longitude coordinates of the final specified location
     * @param walking_dist distance user can walk
     */
    void add_final_location(double latitude,double longitude,long double walking_dist);
    /**
     * Function that invokes the bfs function and returns the best path with less stops made from node a to b.
     * @param a int representing the starting node we want to calculate the best path from
     * @param b int representing the final node we want to calculate the best path to
     * @return list of integers that represent the best path from node a to node b
     */
    list<int> unweighted_path(int a,int b);
    /**
     * Calculates the distance in terms of less number of bus lines changes to every node of the graph starting on the start node s
     * @param s int representing the node in which we want to start and calculate the distance to the other nodes
     * Complexity O(n)= Elog|V| where E is the number of edges and V the number of vertices
     */
    void dijkstra_less_changes(int s);

};

#endif
