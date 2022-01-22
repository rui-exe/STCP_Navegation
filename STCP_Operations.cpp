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

}

STCP_Operations::STCP_Operations(){
    stcp = Graph( number_of_lines_in_file("stops.csv")-1,true);
    read_stops();
    cout << "gg";
}