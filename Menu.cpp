//
// Created by Rui on 24/01/2022.
//

#include "Menu.h"

const char INVALID_KEY = 0;
const string INVALID_STRING;
const double INVALID = -1.0;

double read_double() {
    double n;
    cin >> n;
    if (cin.eof()) {
        exit(EXIT_SUCCESS);
    }
    else if (cin.fail() or cin.peek() != '\n') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return INVALID;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return n;
}

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
    while (!cin.eof() and option != '4') {
        cout<<endl;
        cout << "Please enter an option" << endl;
        cout << "1. Plan Trip" << endl;
        cout << "2. Close station" << endl;
        cout << "3. Open station" << endl;
        cout << "4. Exit" << endl;
        cout<<endl;
        option=readChar();
        switch (option) {
            case '1': {
                plan_trip();
                break;
            }
            case '2': {
                close_stations();
                break;
            }
            case '3': {
                open_stations();
                break;
            }
            case '4':{
                continue;
            }
            default:{
                cout << "The option you entered is invalid. " << endl;
                break;
            }
        }
    }
}

void Menu::plan_trip() {
    bool day;
    cout<<"Day or Night? (1 for day 0 for night): ";
    cin>> day;
    if(day)
        g = operations.getStcpDay();
    else
        g = operations.getStcpNight();
    long double walking_dist;
    char option;
    cout<<"How many km are you willing to walk on foot: ";
    cin>>walking_dist;

    auto start = chrono::high_resolution_clock::now();
    cout << endl<<"Creating graph....";
    g.add_walking(walking_dist);
    auto stop = chrono::high_resolution_clock::now();
    cout << endl << "Graph created in: " << chrono::duration_cast<chrono::seconds>(stop-start).count()<<" secs"<<endl;

    while (!cin.eof() and option != '5') {
        cout<<endl;
        cout << "Please enter an option" << endl;
        cout << "1. Station to station" << endl;
        cout << "2. Station to Coordinate" << endl;
        cout << "3. Coordinate to Station" << endl;
        cout << "4. Coordinate to Coordinate" << endl;
        cout << "5. Exit" << endl;
        cout<<endl;
        option=readChar();
        switch (option) {
            case '1': {
                station_to_station(walking_dist);
                break;
            }
            case '2':{
                station_to_coordinate(walking_dist);
                break;
            }
            case '3':{
                coordinate_to_station(walking_dist);
                break;
            }
            case '4':{
                coordinate_to_coordinate(walking_dist);
                break;
            }
            case '5':{
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
    char method = choose_method();
    switch (method) {
        case'1':{
            less_changes(g,code_to_node[stationA],code_to_node[stationB],walking_dist);
            break;
        }
        case '2': {
            less_stops(g,code_to_node[stationA],code_to_node[stationB],walking_dist);
            break;
        }
        case '3': {
            less_distance(g,code_to_node[stationA],code_to_node[stationB],walking_dist);
            break;
        }
        case '4':{
            less_zones(g,code_to_node[stationA],code_to_node[stationB],walking_dist);
            break;
        }
    }
}

void Menu::coordinate_to_station(long double walking_dist) {
    string station;
    double latitude, longitude;
    cout<<endl;
    cout << "Latitude of start coordinate  ";
    latitude = read_double();
    cout << "Latitude of start coordinate  ";
    longitude= read_double();
    cout << "Code of Final Station: ";
    station=read_string();
    Graph g_copy(g);
    g_copy.add_initial_location(latitude, longitude,walking_dist);
    code_to_node["LI"] = g_copy.n;
    char method = choose_method();
    switch (method) {
        case'1':{
            less_changes(g_copy,g_copy.n,code_to_node[station],walking_dist);
            break;
        }
        case '2': {
            less_stops(g_copy,g_copy.n,code_to_node[station],walking_dist);
            break;
        }
        case '3': {
            less_distance(g_copy,g_copy.n,code_to_node[station],walking_dist);
            break;
        }
        case '4':{
            less_zones(g_copy,g_copy.n,code_to_node[station],walking_dist);
            break;
        }
    }
    code_to_node.erase("LI");
}

void Menu::coordinate_to_coordinate (long double walking_dist) {
    double latitude1, longitude1, latitude2, longitude2;
    cout<<endl;
    cout << "Latitude of start coordinate  ";
    latitude1 = read_double();
    cout << "Latitude of start coordinate  ";
    longitude1= read_double();
    cout << "Latitude of end coordinate  ";
    latitude2 = read_double();
    cout << "Latitude of end coordinate  ";
    longitude2= read_double();
    Graph g_copy(g);
    g_copy.add_initial_location(latitude1, longitude1,walking_dist);
    g_copy.add_final_location(latitude2,longitude2,walking_dist);
    code_to_node["LI"] = g_copy.n-1;
    code_to_node["LF"] = g_copy.n;
    char method = choose_method();
    switch (method) {
        case'1':{
            less_changes(g_copy,g_copy.n-1,g_copy.n,walking_dist);
            break;
        }
        case '2': {
            less_stops(g_copy,g_copy.n-1,g_copy.n,walking_dist);
            break;
        }
        case '3': {
            less_distance(g_copy,g_copy.n-1,g_copy.n,walking_dist);
            break;
        }
        case '4':{
            less_zones(g_copy,g_copy.n-1,g_copy.n,walking_dist);
            break;
        }
    }
    code_to_node.erase("LI");
    code_to_node.erase("LF");
}

void Menu::station_to_coordinate(long double walking_dist) {
    string station;
    double latitude, longitude;
    cout<<endl;
    cout << "Code of Start Station: ";
    station=read_string();
    cout << "Latitude of end coordinate  ";
    latitude = read_double();
    cout << "Latitude of end coordinate  ";
    longitude= read_double();
    Graph g_copy(g);
    g_copy.add_final_location(latitude,longitude,walking_dist);
    code_to_node["LF"] = g_copy.n;
    char method = choose_method();
    switch (method) {
        case'1':{
            less_changes(g_copy,code_to_node[station],g_copy.n,walking_dist);
            break;
        }
        case '2': {
            less_stops(g_copy,code_to_node[station],g_copy.n,walking_dist);
            break;
        }
        case '3': {
            less_distance(g_copy,code_to_node[station],g_copy.n,walking_dist);
            break;
        }
        case '4':{
            less_zones(g_copy,code_to_node[station],g_copy.n,walking_dist);
            break;
        }
    }
    code_to_node.erase("LF");
}

char Menu::choose_method() {
    char answer;
    cout<<endl;
    cout << "Please enter an option." << endl;
    cout << "1. Less Bus Changes." << endl;
    cout << "2. Less Stops." << endl;
    cout << "3. Less Distance Traveled." << endl;
    cout << "4. Less money spent (fewer zones)." << endl;
    cout << "5. Exit." << endl;
    cout<<endl;
    answer = readChar();
    return answer;
}

void Menu::less_stops(Graph g, int initial_node, int final_node, long double walking_dist) {
    auto start = chrono::high_resolution_clock::now();
    cout << endl;
    list<int> stops_changes = g.unweighted_path(initial_node,final_node);
    for (int stop: stops_changes) {
        cout << "Paragem: " << g.nodes[stop].name << "  Codigo: "
             << g.nodes[stop].code << " Linha apanhada: " <<
             g.nodes[stop].line << "  Zona: " << g.nodes[stop].zone << endl;
    }
    auto stop = chrono::high_resolution_clock::now();
    cout << endl << "Results given in: " << chrono::duration_cast<chrono::seconds>(stop-start).count()<<" secs"<<endl;
}

void Menu::less_changes(Graph g, int initial_node, int final_node, long double walking_dist){
    auto start = chrono::high_resolution_clock::now();
    cout << endl;
    list<int> stops =  g.dijkstra_less_changes_path(initial_node,final_node,code_to_node);
    for(int stop:stops){
        cout << "Paragem: " << g.nodes[stop].name << "  Codigo: " << g.nodes[stop].code << " Linha a apanhar: "<<
             g.nodes[stop].line << "  Zona: " <<g.nodes[stop].zone<<endl;
    }
    auto stop = chrono::high_resolution_clock::now();
    cout << endl << "Results given in: " << chrono::duration_cast<chrono::seconds>(stop-start).count()<<" secs"<<endl;
}

void Menu::less_distance(Graph g, int initial_node, int final_node, long double walking_dist) {
    auto start = chrono::high_resolution_clock::now();
    cout << endl;
    list<int> stops_distance = g.dijkstra_less_length_path(initial_node,final_node,code_to_node);
    for (int stop: stops_distance) {
        cout << "Paragem: " << g.nodes[stop].name << "  Codigo: "
             << g.nodes[stop].code
             << " Linha a apanhar: " << g.nodes[stop].line << "  Zona: "
             << g.nodes[stop].zone << endl;
    }
    auto stop = chrono::high_resolution_clock::now();
    cout << endl << "Results given in: " << chrono::duration_cast<chrono::seconds>(stop-start).count()<<" secs"<<endl;
    cout << "Distance traveled = " << g.nodes[stops_distance.back()].dist << " km" << endl;
}

void Menu::less_zones(Graph g, int initial_node, int final_node, long double walking_dist) {
    auto start = chrono::high_resolution_clock::now();
    cout << endl;
    list<int> zones_distance = g.dijkstra_less_zones_path(initial_node,final_node,code_to_node);
    for(int stop:zones_distance){
        cout << "Paragem: "<< g.nodes[stop].name << "  Codigo: " << g.nodes[stop].code << " Linha a apanhar: "
             <<g.nodes[stop].line << "  Zona: "<<g.nodes[stop].zone<<endl;
    }
    auto stop = chrono::high_resolution_clock::now();
    cout << endl << "Results given in: " << chrono::duration_cast<chrono::seconds>(stop-start).count()<<" secs"<<endl;
}

void Menu::close_stations(){
    int nr_stops_closed;
    string station_to_close;
    cout<<"How many stations do you want to close: ";
    cin>> nr_stops_closed;
    for(int c=0; c<nr_stops_closed;c++){
        cout<<"Code of the station you wish to close: ";
        station_to_close = read_string();
        operations.close_station(station_to_close);
    }
}

void Menu::open_stations(){
    int nr_stops_opened;
    string station_to_close;
    cout<<"How many stations do you want to open: ";
    cin>> nr_stops_opened;
    for(int c=0; c<nr_stops_opened;c++){
        cout<<"Code of the station you wish to open: ";
        station_to_close = read_string();
        operations.open_station(station_to_close);
    }
}
