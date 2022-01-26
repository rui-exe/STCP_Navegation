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
    /**
     * Constructor of the class Menu.
     * It essentially creates the object of the class STCP_Operations of which we will get our graph and also initializes
     * the unordered_map code_to_node so it can map our graph's nodes.
     */
    Menu(){operations = STCP_Operations();code_to_node = operations.get_code_to_node();}
    /**
     * Simple menu interface to display to the user.
     */
    void interface();
    /**
     * Another interface to let the user choose what's best for him.
     */
    void plan_trip();
    /**
     * User interface that reads an initial station's and final station's code. And then evokes the correct function depending
     * on the what the user chose (choose_method() function).
     * @param walking_dist a long double that represents the distance that the user is willing to travel on foot.
     */
    void station_to_station(long double walking_dist);
    /**
     * User interface that reads an initial latitude and longitude and a final station's code. And then evokes the correct function depending
     * on the what the user chose (choose_method() function).
     * @param walking_dist a long double that represents the distance that the user is willing to travel on foot.
     */
    void coordinate_to_station(long double walking_dist);
    /**
     * User interface that reads an initial station's code final latitude and longitude. And then evokes the correct function depending
     * on the what the user chose (choose_method() function).
     * @param walking_dist a long double that represents the distance that the user is willing to travel on foot.
     */
    void station_to_coordinate(long double walking_dist);
    /**
     * User interface that reads an initial and final latitude and longitude. And then evokes the correct function depending
     * on the what the user chose (choose_method() function).
     * @param walking_dist a long double that represents the distance that the user is willing to travel on foot.
     */
    void coordinate_to_coordinate(long double walking_dist);
    /**
     * An interface that let's the user choose if he wants the path with:
     * less stops, or less bus changes, or less distance, or simply cheaper (less zones)
     * @return
     */
    char choose_method();
    /**
     * This function outputs the best path with less stops that the user will have to follow.
     * @param g the graph on which the algorithm will be applied
     * @param initial_node int representing the node of the initial location where the user departs from.
     * @param final_node int representing the node of the final location where the user arrives to.
     * @param walking_dist a long double that represents the distance that the user is willing to travel on foot.
     */
    void less_stops(Graph g, int initial_node, int final_node, long double walking_dist);
    /**
     * This function outputs the best path with less bus changes that the user will have to follow.
     * @param g the graph on which the algorithm will be applied
     * @param initial_node int representing the node of the initial location where the user departs from.
     * @param final_node int representing the node of the final location where the user arrives to.
     * @param walking_dist a long double that represents the distance that the user is willing to travel on foot.
     */
    void less_changes(Graph g, int initial_node, int final_node, long double walking_dist);
    /**
     * This function outputs the best path with less distance traveled that the user will have to follow.
     * @param g the graph on which the algorithm will be applied
     * @param initial_node int representing the node of the initial location where the user departs from.
     * @param final_node int representing the node of the final location where the user arrives to.
     * @param walking_dist a long double that represents the distance that the user is willing to travel on foot.
     */
    void less_distance(Graph g, int initial_node, int final_node, long double walking_dist);
    /**
     * This function outputs the cheaper path with less zones that the user will have to follow.
     * @param g the graph on which the algorithm will be applied
     * @param initial_node int representing the node of the initial location where the user departs from.
     * @param final_node int representing the node of the final location where the user arrives to.
     * @param walking_dist a long double that represents the distance that the user is willing to travel on foot.
     */
    void less_zones(Graph g, int initial_node, int final_node, long double walking_dist);

    /**
     * This function lets the user choose stations that he doesn't want to use
     */
    void close_stations();

    /**
    * This function lets the user choose stations that he doesn't want to open
    */
    void open_stations();
};


#endif //STCP_NAVEGATION_MENU_H
