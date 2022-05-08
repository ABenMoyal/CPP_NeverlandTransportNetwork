//
// Created by adirr on 08/05/2022.
//

#ifndef HW2_SIMULATION_H
#define HW2_SIMULATION_H
#include <array>
#include <iostream>
#include <vector>
#include "Utils/Config.h"
#include "Graph/Graph.h"
#include "Terminal/Terminal.h"

using namespace std;

class Simulation {
private:
    string config_file_name, output_file_name;
    vector<string> input_files;
    Config config;
    Terminal terminal;
    Graph graph;
    void ParseArgs(int argc, char *argv[]);
public:
    void Start(int argc, char* argv[]);
};


#endif //HW2_SIMULATION_H
