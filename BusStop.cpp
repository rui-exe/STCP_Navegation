//
// Created by Rui on 22/01/2022.
//

#include "BusStop.h"

string BusStop::get_code() const{
    return code;
}

string BusStop::get_name() const{
    return name;
}

string BusStop::get_zone() const{
    return zone;
}
double BusStop::get_latitude() const{
    return latitude;
}

double BusStop::get_longitude() const {
    return longitude;
};
