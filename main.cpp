#include <iostream>
#include "STCP_Operations.h"
int main() {
    STCP_Operations operations = STCP_Operations();
    unordered_map<string,int> code_to_node = operations.get_code_to_node();
    /*
    list<int> stops_distance = operations.getStcp().dijkstra_less_length_path(code_to_node["FEUP1"],code_to_node["FCUP1"]);
    for(int stop:stops_distance){
        cout << operations.getStcp().nodes[stop].name << "--" << operations.getStcp().nodes[stop].code << "--" <<operations.getStcp().nodes[stop].line << "---"<<
             operations.getStcp().nodes[stop].zone<<endl;
    }
    cout << endl << "------" << endl << endl;

     */
    /*

    Graph g = operations.getStcp_reference();
    list<int> stops_changes = operations.getStcp_reference().dijkstra_less_changes_path(code_to_node["VALC1"],code_to_node["CMP1"],code_to_node);


    for(int stop:stops_changes){
        cout << "Paragem: " << operations.getStcp_reference().nodes[stop].name << "  Codigo: " << operations.getStcp_reference().nodes[stop].code << " Linha a apanhar: "<<
      operations.getStcp_reference().nodes[stop].line << "  Zona: " <<operations.getStcp_reference().nodes[stop].zone<<endl;
    }
    */
    /*
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
    Graph stcp_copy =operations.getStcp_copy();
    /*
    stcp_copy.add_location(41.18292646606174, -8.598989323909137);
    stcp_copy.add_location(41.17880629312572, -8.693166401315493);
    */
    stcp_copy.add_walking(1.0);
    cout << endl << endl << endl;
    list<int> stops =  stcp_copy.dijkstra_less_changes_path(code_to_node["FEUP1"],code_to_node["FCUP1"],code_to_node);
    for(int stop:stops){
        cout << "Paragem: " << stcp_copy.nodes[stop].name << "  Codigo: " << stcp_copy.nodes[stop].code << " Linha a apanhar: "<<
       stcp_copy.nodes[stop].line << "  Zona: " <<stcp_copy.nodes[stop].zone<<endl;
    }

    /*
    cout << "----------------" << endl;

    Graph station_to_b =operations.getStcp().station_to_b(41.18292646606174, -8.598989323909137);
    Graph station_to_b_walking = station_to_b.add_walking(0.5);
    list<int> stops2 =  station_to_b_walking.dijkstra_less_changes_path(code_to_node["JB1"],station_to_b_walking.n);
    for(int stop:stops2){
        cout << station_to_b_walking.nodes[stop].name << "--" << station_to_b_walking.nodes[stop].code << "--" <<station_to_b_walking.nodes[stop].line << "---"<<
        station_to_b_walking.nodes[stop].zone<<endl;
    }
    */
}
