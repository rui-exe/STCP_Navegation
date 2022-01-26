//
// Created by Rui on 22/01/2022.
//

#ifndef STCP_NAVEGATION_STCP_OPERATIONS_H
#define STCP_NAVEGATION_STCP_OPERATIONS_H

#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include "graph.h"
using namespace std;

class STCP_Operations {
private:
    unordered_map<string,int> code_to_node;
    Graph stcp_day = Graph(0);
    Graph stcp_night = Graph(0);
    /**
     * Private function that reads all the stops and assigns them to the nodes of the "stcp" graph
     */
    void read_stops();
    /**
     * Private function that reads all the lines and creates edges from stop1 to stop2
     * (stop1 and stop2 are nodes of the "stcp" graph
     */
    void read_lines();
public:
    /**
     * Default Constructor of the class STCP_Operations.
     * It creates a directed graph containing the same number of nodes as the number of stops existent on the stops.csv file
     * Also calls the read stops and readline functions.
     */
    STCP_Operations();
    /**
     * Simple getter for the graph "stcp_day"
     * @return an instance of the Graph class which is our stcp_day Graph.
     */
    Graph getStcpDay();
    /**
     * Simple getter for the graph "stcp_night"
     * @return an instance of the Graph class which is our stcp_night Graph.
     */
    Graph getStcpNight();
    /**
     * Simple getter for our unordered_map that maps the code of a bus stop to the int representing that stop on the graph
     * @return
     */
    unordered_map<string,int> get_code_to_node();
    /**
     *
     * @param code - station code
     * closes the station with the code given as input
     */
    void close_station(const string& code);
    /**
     *
     * @param code - station code
     * opens the station with the code given as input
     */
    void open_station(const string& code);
};


#endif //STCP_NAVEGATION_STCP_OPERATIONS_H
