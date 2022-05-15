//
// Created by adirr on 02/05/2022.
//

#ifndef HW2_FILEREADER_H
#define HW2_FILEREADER_H
#include <iostream>
#include "../Graph/Graph.h"
#include "Config.h"
#include "../TransportNetwork/TransportNetwork.h"

using namespace std;

class FileReader {
public:
    static void ReadInputFileAndUpdateNetwork(const string&, TransportNetwork&, const Config&);
    static Config ReadConfigFile(const string& config_file);
};


#endif //HW2_FILEREADER_H
