//
// Created by adirr on 04/05/2022.
//

#ifndef HW2_GRAPH_H
#define HW2_GRAPH_H

#include "../Utils/IOStructs.h"
#include "../Utils/UtilsFunctions.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Graph {
private:
    vector<vector<int> > transportGraph;  // data
    map<string, int> stationIXMap;  // StationName to Index in data
    int stationIXCount;  // Station Index Counter
public:
    Graph() {stationIXCount = 0;}
    void AddStationToTransportGraph();
    void UpdateGraph(LoadCmdInput& input);
    string GetStationNameByIX(int ix);
    vector<string> BFS(const string &source, bool transpose = false);
    bool ContainsNode(const string &nodeName);
    vector<string> GetNeighboursNames(const string& nodeName);
    vector<string> GetNodesNames();
};


#endif //HW2_GRAPH_H
