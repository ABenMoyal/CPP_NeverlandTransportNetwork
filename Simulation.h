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
#include "TransportNetwork/TransportNetwork.h"

using namespace std;

class Simulation {
private:
    string config_file_name, output_file_name;
    vector<string> input_files;
    Config config;
    Terminal terminal;
    TransportNetwork transportNetwork{};
    void ParseArgs(int argc, char *argv[]);
public:
    Simulation(int argc, char* argv[]);
    void Start();
};


#endif //HW2_SIMULATION_H
