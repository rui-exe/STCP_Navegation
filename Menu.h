//
// Created by Rui on 24/01/2022.
//

#ifndef STCP_NAVEGATION_MENU_H
#define STCP_NAVEGATION_MENU_H
#include <iostream>
#include <limits>
#include <string>
#include <iomanip>
#include "STCP_Operations.h"

using namespace std;

class Menu {
private:
    STCP_Operations operations;
    unordered_map<string,int> code_to_node;
public:
    Menu(){operations = STCP_Operations();code_to_node = operations.get_code_to_node();}
    void interface();
    void plan_trip(bool walking);
    void station_to_station(long double walking_dist);

    void coordinate_to_station(long double walking_dist);

    void coordinate_to_coordinate(long double walking_dist);
};


#endif //STCP_NAVEGATION_MENU_H
