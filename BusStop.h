//
// Created by Rui on 22/01/2022.
//

#ifndef STCP_NAVEGATION_BUSSTOP_H
#define STCP_NAVEGATION_BUSSTOP_H

#include "string"

using namespace std;

class BusStop {
private:
    string code;
    string name;
    string zone;
    double latitude;
    double longitude;
public:
    string get_code() const;
    string get_name() const;
    string get_zone() const;
    double get_latitude() const;
    double get_longitude() const;
};


#endif //STCP_NAVEGATION_BUSSTOP_H
