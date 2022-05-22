//
// Created by adirr on 04/05/2022.
//

#ifndef HW2_GRAPH_H
#define HW2_GRAPH_H

#include "../Utils/IOStructs.h"
#include "../Utils/UtilsFunctions.h"
#include "../Utils/Config.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Graph {
private:
    vector<vector<int> > transportGraph;  // data
    map<string, int> stationIXMap;  // StationName to Index in data
    int stationIXCount;  // Station Index Counter
    bool isMergedGraph;
    VehicleName vehicleName;
public:
    Graph(bool isMergedGraph = false, VehicleName vehicleName=BUS) : isMergedGraph(isMergedGraph),
                                                                   vehicleName(vehicleName) { stationIXCount = 0; }

    void AddStationToTransportGraph();

    void UpdateGraph(Edge &input);

    string GetStationNameByIX(int ix) const;

    vector<string> BFS(const string &source, bool transpose = false);

    bool ContainsNode(const string &nodeName) const;

    vector<string> GetNeighboursNames(const string &nodeName) const;

    vector<string> GetNodesNames() const;

    map<string, double> Dijkstra(const string &sourceNode, const string &destNode, const Config &config) const;

    bool IsMergedGraph() const { return isMergedGraph; }

    const VehicleName &GetVehicleName() const { return vehicleName; }
};


#endif //HW2_GRAPH_H
