#include <iostream>
#include "STCP_Operations.h"
int main() {
    STCP_Operations operations = STCP_Operations();
    map<string,int> code_to_node = operations.get_code_to_node();
    /*
    list<int> stops_distance = operations.getStcp().dijkstra_less_length_path(code_to_node["FEUP1"],code_to_node["FCUP1"]);
    for(int stop:stops_distance){
        cout << operations.getStcp().nodes[stop].name << "--" << operations.getStcp().nodes[stop].code << "--" <<operations.getStcp().nodes[stop].line << "---"<<
             operations.getStcp().nodes[stop].zone<<endl;
    }
    cout << endl << "------" << endl << endl;


    list<int> stops_changes = operations.getStcp().dijkstra_less_changes_path(code_to_node["FEUP1"],code_to_node["FCUP1"]);

    for(int stop:stops_changes){
        cout << operations.getStcp().nodes[stop].name << "--" << operations.getStcp().nodes[stop].code << "--" <<operations.getStcp().nodes[stop].line << "----" <<
             operations.getStcp().nodes[stop].zone<<endl;
    }

    cout << endl << "------" << endl << endl;
    list<int> min_stops = operations.getStcp().unweighted_path(code_to_node["FEUP1"],code_to_node["FCUP1"]);
    string line_2 = operations.getStcp().nodes[min_stops.front()].line;
    for(int stop:min_stops){
        cout << operations.getStcp().nodes[stop].name << "--" << operations.getStcp().nodes[stop].code << "--" <<operations.getStcp().nodes[stop].line << "---"<<
             operations.getStcp().nodes[stop].zone<<endl;
    }


    cout << endl << "------" << endl << endl;

    list<int> zones_distance = operations.getStcp().dijkstra_less_zones_path(code_to_node["FEUP1"],code_to_node["FCUP1"]);
    for(int stop:zones_distance){
        cout << operations.getStcp().nodes[stop].name << "--" << operations.getStcp().nodes[stop].code << "--" <<operations.getStcp().nodes[stop].line << "---"<<
             operations.getStcp().nodes[stop].zone<<endl;
    }
    return 0;
    */
    Graph walking_graph = operations.getStcp().add_walking(2.0);
    list<int> stops =  walking_graph.dijkstra_less_zones_path(code_to_node["VALC1"],code_to_node["FCUP1"]);
    for(int stop:stops){
        cout << walking_graph.nodes[stop].name << "--" << walking_graph.nodes[stop].code << "--" <<walking_graph.nodes[stop].line << "---"<<
             operations.getStcp().nodes[stop].zone<<endl;
    }
}
