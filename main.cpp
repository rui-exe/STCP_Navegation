#include <iostream>
#include <chrono>
#include "STCP_Operations.h"
using namespace std;
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
    auto start = chrono::high_resolution_clock::now();
    Graph stcp_copy =operations.getStcp_copy();
    stcp_copy.add_initial_location(41.18298602687737, -8.598950817803937);
    code_to_node["LI"] = stcp_copy.n;
    stcp_copy.add_final_location(41.179271615778745, -8.690640977538155);
    code_to_node["LF"] = stcp_copy.n;
    stcp_copy.add_walking(3.0);
    cout << endl << endl << endl;
    list<int> stops =  stcp_copy.dijkstra_less_changes_path(stcp_copy.n-1,stcp_copy.n,code_to_node);
    for(int stop:stops){
        cout << "Paragem: " << stcp_copy.nodes[stop].name << "  Codigo: " << stcp_copy.nodes[stop].code << " Linha a apanhar: "<<
       stcp_copy.nodes[stop].line << "  Zona: " <<stcp_copy.nodes[stop].zone<<endl;
    }
    auto stop = chrono::high_resolution_clock::now();
    cout << endl << "Results given in: " << chrono::duration_cast<chrono::seconds>(stop-start).count();

    /*
    Graph g(2);
    g.nodes[1].latitude=41.18296521099278;
    g.nodes[1].longitude=-8.598970755099034;
    g.nodes[2].latitude=41.1831144;
    g.nodes[2].longitude=-8.599711386;
    cout << endl << endl << "Dist: " << Graph::dist_stops(g.nodes[1],g.nodes[2]);
     */
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
