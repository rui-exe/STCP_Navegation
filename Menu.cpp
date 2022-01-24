//
// Created by Rui on 24/01/2022.
//

#include "Menu.h"

const char INVALID_KEY = 0;
const string INVALID_STRING = "";

string read_string(){
    string s;
    cin >> s;
    if (cin.eof()) {
        exit(EXIT_SUCCESS);
    }
    else if (cin.peek() != '\n') {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return INVALID_STRING;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return s;
}

char readChar() {
    char c;
    cin >> c;
    if (cin.eof()) {
        exit(EXIT_SUCCESS);
    }
    else if (cin.peek() != '\n') {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return INVALID_KEY;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return c;
}

void Menu::interface() {
    char option;
    while (!cin.eof() and option != '2') {
        cout<<endl;
        cout << "Please enter an option" << endl;
        cout << "1. Plan Trip" << endl;
        cout << "2. Exit" << endl;
        cout<<endl;
        option=readChar();
        switch (option) {
            case '1': {
                bool walking;
                cout<<"Are you willing to walk (0|1): ";
                cin>>walking;
                plan_trip(walking);
                break;
            }
            case '2':{
                continue;
            }
            default:{
                cout << "The option you entered is invalid. " << endl;
                break;
            }
        }
    }
}

void Menu::plan_trip(bool walking) {
    long double walking_dist=0.0;
    char option;
    if(walking){
        cout<<"How many km are you willing to walk on foot (max:1km): ";
        cin>>walking_dist;
    }
    while (!cin.eof() and option != '4') {
        cout<<endl;
        cout << "Please enter an option" << endl;
        cout << "1. Station to station" << endl;
        cout << "2. Coordinate to station or vice versa" << endl;
        cout << "3. Coordinate to Coordinate" << endl;
        cout << "4. Exit" << endl;
        cout<<endl;
        option=readChar();
        switch (option) {
            case '1': {
                station_to_station(walking_dist);
                break;
            }
            case '2':{
                coordinate_to_station(walking_dist);
                break;
            }
            case '3':{
                coordinate_to_coordinate(walking_dist);
                break;
            }
            case '4': {
                continue;
            }
            default:{
                cout << "The option you entered is invalid. " << endl;
                break;
            }
        }
    }
}

void Menu::station_to_station(long double walking_dist) {
    string stationA,stationB;
    cout<<endl;
    cout << "Code of Station A: ";
    stationA=read_string();
    cout << "Code of Station B: ";
    stationB = read_string();
    char option;
    cout << "Please enter an option" << endl;
    cout << "1. Less stops" << endl;
    cout << "2. Less distance" << endl;
    cout << "3. Less line changes" << endl;
    cout << "4. Less cost (total zones)" << endl;
    option = readChar();
    Graph stcp_reference = operations.getStcp_reference();
    stcp_reference.add_walking(walking_dist);
    switch (option) {
        case '1': {
            list<int> stops_changes = stcp_reference.unweighted_path(code_to_node[stationA],
                                                                     code_to_node[stationB]);
            for (int stop: stops_changes) {
                cout << "Paragem: " << stcp_reference.nodes[stop].name << "  Codigo: "
                     << stcp_reference.nodes[stop].code << " Linha apanhada: " <<
                     stcp_reference.nodes[stop].line << "  Zona: " << stcp_reference.nodes[stop].zone << endl;
            }
            break;
        }
        case '2':{
            list<int> stops_distance = stcp_reference.dijkstra_less_length_path(code_to_node[stationA],
                                                                                code_to_node[stationB]);
            for (int stop: stops_distance) {
                cout << "Paragem: " << stcp_reference.nodes[stop].name << "  Codigo: "
                     << stcp_reference.nodes[stop].code
                     << " Linha a apanhar: " << stcp_reference.nodes[stop].line << "  Zona: "
                     << stcp_reference.nodes[stop].zone << endl;
            }
            cout << endl << "------" << endl << endl;
            cout << "Distance traveled = " << stcp_reference.nodes[stops_distance.back()].dist << " km" << endl;

            break;
        }
        case '3': {
            Graph stcp_copy = operations.getStcp_copy();
            stcp_copy.add_walking(walking_dist);
            list<int> stops = stcp_copy.dijkstra_less_changes_path(code_to_node[stationA], code_to_node[stationB],
                                                                   code_to_node);
            for (int stop: stops) {
                cout << "Paragem: " << stcp_copy.nodes[stop].name << "  Codigo: " << stcp_copy.nodes[stop].code
                     << " Linha a apanhar: " << stcp_copy.nodes[stop].line << "  Zona: " << stcp_copy.nodes[stop].zone
                     << endl;
            }
            break;
        }
        case '4': {

            list<int> zones_distance = stcp_reference.dijkstra_less_zones_path(code_to_node["FEUP1"],code_to_node["FCUP1"]);
            for(int stop:zones_distance){
                cout << "Paragem: "<< stcp_reference.nodes[stop].name << "  Codigo: " << stcp_reference.nodes[stop].code << " Linha a apanhar: "
                <<stcp_reference.nodes[stop].line << "  Zona: "<<stcp_reference.nodes[stop].zone<<endl;
            }
            break;
        }
        default:{
            cout << "The option you entered is invalid. " << endl;
            break;
        }
    }
}

void Menu::coordinate_to_station(long double walking_dist) {

}

void Menu::coordinate_to_coordinate (long double walking_dist) {

}



