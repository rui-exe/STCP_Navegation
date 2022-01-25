//
// Created by Rui on 24/01/2022.
//

#ifndef STCP_NAVEGATION_MENU_H
#define STCP_NAVEGATION_MENU_H
#include <iostream>
#include <limits>
#include <string>
#include <iomanip>
#include <chrono>
#include "STCP_Operations.h"

using namespace std;

class Menu {
private:
    Graph g = Graph(0);
    STCP_Operations operations;
    unordered_map<string,int> code_to_node;
public:
    Menu(){operations = STCP_Operations();code_to_node = operations.get_code_to_node();}
    void interface();
    void plan_trip();
    void station_to_station(long double walking_dist);

    void coordinate_to_station(long double walking_dist);

    void station_to_coordinate(long double walking_dist);

    void coordinate_to_coordinate(long double walking_dist);

    char choose_method();

    void less_stops(Graph g, int initial_node, int final_node, long double walking_dist);

    void less_changes(Graph g, int initial_node, int final_node, long double walking_dist);

    void less_distance(Graph g, int initial_node, int final_node, long double walking_dist);

    void less_zones(Graph g, int initial_node, int final_node, long double walking_dist);
};


#endif //STCP_NAVEGATION_MENU_H
