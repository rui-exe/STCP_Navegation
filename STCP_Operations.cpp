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
    input_file.open("dataset/stops.csv");
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
        stcp_night.nodes[i].code = code;
        stcp_night.nodes[i].name = name;
        stcp_night.nodes[i].zone = zone;
        stcp_night.nodes[i].latitude = latitude;
        stcp_night.nodes[i].longitude = longitude;
        stcp_night.nodes[i].closed = false;
        stcp_day.nodes[i].code = code;
        stcp_day.nodes[i].name = name;
        stcp_day.nodes[i].zone = zone;
        stcp_day.nodes[i].latitude = latitude;
        stcp_day.nodes[i].longitude = longitude;
        stcp_day.nodes[i].closed = false;
        i++;
    }

}

void STCP_Operations::read_lines(){
    ifstream input_file;
    string line;
    input_file.open("dataset/lines.csv");
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
        line_file0.open("dataset/line_"+ bus_line+"_0.csv");
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
                if(bus_line.back()=='M')
                    stcp_night.addEdge(previous_node, current_node, bus_line+"_0", Graph::dist_stops(stcp_night.nodes[previous_node], stcp_night.nodes[current_node]));
                else
                    stcp_day.addEdge(previous_node, current_node, bus_line+"_0", Graph::dist_stops(stcp_day.nodes[previous_node], stcp_day.nodes[current_node]));
                previous_bus_stop0 = current_bus_stop0;
                number_stops_in_line--;
            }
        }
        ifstream line_file1;
        line_file1.open("dataset/line_"+ bus_line+"_1.csv");
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
                if(bus_line.back()=='M')
                    stcp_night.addEdge(previous_node, current_node, bus_line+"_1", Graph::dist_stops(stcp_night.nodes[previous_node], stcp_night.nodes[current_node]));
                else
                    stcp_day.addEdge(previous_node, current_node, bus_line+"_1", Graph::dist_stops(stcp_day.nodes[previous_node], stcp_day.nodes[current_node]));
                previous_bus_stop1 = current_bus_stop1;
                number_stops_in_line--;
            }
        }
    }
}

Graph STCP_Operations::getStcpNight() {
    return stcp_night;
}

Graph STCP_Operations::getStcpDay() {
    return stcp_day;
}

unordered_map<string,int> STCP_Operations::get_code_to_node(){
    return code_to_node;
}

STCP_Operations::STCP_Operations(){
    stcp_night = Graph( number_of_lines_in_file("dataset/stops.csv")-1,true);
    stcp_day = Graph( number_of_lines_in_file("dataset/stops.csv")-1,true);
    read_stops();
    read_lines();
}
