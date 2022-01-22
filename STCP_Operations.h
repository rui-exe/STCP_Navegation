//
// Created by Rui on 22/01/2022.
//

#ifndef STCP_NAVEGATION_STCP_OPERATIONS_H
#define STCP_NAVEGATION_STCP_OPERATIONS_H

#include <fstream>
#include <sstream>
#include <map>
#include "graph.h"
using namespace std;

class STCP_Operations {
private:
    map<string,int> code_to_node;
    void read_stops();
public:
    STCP_Operations();

};


#endif //STCP_NAVEGATION_STCP_OPERATIONS_H
