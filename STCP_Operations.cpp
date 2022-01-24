//
// Created by Rui on 22/01/2022.
//

#include "STCP_Operations.h"


int number_of_lines_in_file(string file_name){
    int number_of_lines = 0;
    string line;
    ifstream myfile(file_name);
    while (getline(myfile, line))
        ++number_of_lines;
    myfile.close();
    return number_of_lines;
}



void STCP_Operations::read_stops(){
    ifstream input_file;
    string line;
    int i=1;
    input_file.open("stops.csv");
    getline(input_file,line);
    while(getline(input_file,line)){
        vector<string> words;
        string word;
        stringstream ssline(line);
        while(getline(ssline,word,','))
            words.push_back(word);
        string code=words[0],name=words[1],zone=words[2];
        double latitude=stod(words[3]),longitude=stod(words[4]);
        code_to_node[code]=i;
        stcp.nodes[i].code = code;
        stcp.nodes[i].name = name;
        stcp.nodes[i].zone = zone;
        stcp.nodes[i].latitude = latitude;
        stcp.nodes[i].longitude = longitude;
        i++;
    }

}

void STCP_Operations::read_lines(){
    ifstream input_file;
    string line;
    input_file.open("lines.csv");
    getline(input_file,line);
    while(getline(input_file,line)){
        string aux_number_stops;
        int number_stops_in_line;
        vector<string> words;
        string word;
        stringstream ssline(line);
        while(getline(ssline,word,','))
            words.push_back(word);
        ifstream line_file0;
        string bus_line = words[0];
        line_file0.open("line_"+ bus_line+"_0.csv");
        if(line_file0.is_open()) {
            getline(line_file0, aux_number_stops);
            number_stops_in_line = stoi(aux_number_stops);
            string previous_bus_stop0;
            getline(line_file0, previous_bus_stop0); // starting point
            while (number_stops_in_line > 1) {
                string current_bus_stop0;
                getline(line_file0, current_bus_stop0);
                int previous_node = code_to_node[previous_bus_stop0];
                int current_node = code_to_node[current_bus_stop0];
                stcp.addEdge(previous_node, current_node, bus_line+"_0", Graph::dist_stops(stcp.nodes[previous_node], stcp.nodes[current_node]));
                previous_bus_stop0 = current_bus_stop0;
                number_stops_in_line--;
            }
        }
        ifstream line_file1;
        line_file1.open("line_"+ bus_line+"_1.csv");
        if(line_file1.is_open()) {
            string previous_bus_stop1;
            getline(line_file1,aux_number_stops);
            number_stops_in_line = stoi(aux_number_stops);
            getline(line_file1, previous_bus_stop1); // starting point
            number_stops_in_line = stoi(aux_number_stops);
            while (number_stops_in_line > 1) {
                string current_bus_stop1;
                getline(line_file1, current_bus_stop1);
                int previous_node = code_to_node[previous_bus_stop1];
                int current_node = code_to_node[current_bus_stop1];
                stcp.addEdge(previous_node, current_node, bus_line+"_1", Graph::dist_stops(stcp.nodes[previous_node], stcp.nodes[current_node]));
                previous_bus_stop1 = current_bus_stop1;
                number_stops_in_line--;
            }
        }
    }
}

Graph& STCP_Operations::getStcp_reference() {
    return stcp;
}

Graph STCP_Operations::getStcp_copy() {
    return stcp;
}

unordered_map<string,int> STCP_Operations::get_code_to_node(){
    return code_to_node;
}

STCP_Operations::STCP_Operations(){
    stcp = Graph( number_of_lines_in_file("stops.csv")-1,true);
    read_stops();
    read_lines();
}
