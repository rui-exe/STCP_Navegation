//
// Created by Rui on 22/01/2022.
//

#include "STCP_Operations.h"


int number_of_lines_in_file(string file_name){
    int number_of_lines = 0;
    string line;
    ifstream myfile(file_name + ".txt");
    while (getline(myfile, line))
        ++number_of_lines;
    myfile.close();
    return number_of_lines;
}

void STCP_Operations::read_stops(){
    ifstream input_file;
    string line;
    Graph stcp = Graph( number_of_lines_in_file("dataset/stops.csv")-1,true);
    int i=1;
    input_file.open("dataset/stops.csv");
    getline(input_file,line);
    while(getline(input_file,line)){
        stringstream ssline(line);
        string code,name,zone;
        double latitude,longitude;
        ssline >> code >> name >> zone >> latitude >> longitude;
        code_to_node[code]=i;
        stcp.nodes[i].code = code;
        stcp.nodes[i].name = name;
        stcp.nodes[i].zone = zone;
        stcp.nodes[i].latitude = latitude;
        stcp.nodes[i].longitude = longitude;
        i++;
    }

}

STCP_Operations::STCP_Operations(){
    read_stops();
    cout << "gg";
}