//
// Created by adirr on 04/05/2022.
//

#include "Graph.h"
#include "list"

void Graph::AddStationToTransportGraph(){
    int stIX;
    for (stIX = 0; stIX < transportGraph.size(); stIX++) {
        transportGraph.at(stIX).push_back(-1);
    }
    vector<int> newStation;
    for (stIX = 0; stIX < stationIXCount; stIX++) newStation.push_back(-1);
    transportGraph.push_back(newStation);
}

#define ADD_NEW_STATION_TO_GRAPH_IF_NEEDED(station) { \
    if (stationIXMap.count(station)  == 0) { \
        stationIXMap[station]  = stationIXCount++; \
        AddStationToTransportGraph(); \
    }\
}

void Graph::UpdateGraph(LoadCmdInput *input) {
    ADD_NEW_STATION_TO_GRAPH_IF_NEEDED(input->src);
    ADD_NEW_STATION_TO_GRAPH_IF_NEEDED(input->dest);
    int srcIx = stationIXMap[input->src];
    int dstIx = stationIXMap[input->dest];
    if (transportGraph.at(srcIx).at(dstIx) > input->duration || transportGraph.at(srcIx).at(dstIx) == -1) {
        transportGraph.at(srcIx).at(dstIx) = input->duration;
    }
}

string Graph::GetStationNameByIX(int ix) {
    for (auto &station: stationIXMap) {
        if (station.second == ix) return station.first;
    }
    // TODO: ERROR
    cout << "Graph::GetStationNameByIX ix not found but sent from vector " << endl;
    exit(1);

}

#define ADD_DST_STATION_AS_REACHABLE_IF_NEEDED() { \
    string dstName =  GetStationNameByIX(dstStation); \
    if (!contains(reachables, dstName)) {\
        reachables.push_back(dstName); \
        queue.push_back(dstStation); \
    }\
}
vector<string> Graph::BFS(const string &source, bool transpose) {
    vector<string> reachables;
    list<int> queue;
    int srcIx = stationIXMap[source];

    queue.push_back(srcIx);
    int currSrcStation;
    while (!queue.empty()) {
        currSrcStation = queue.front();
        queue.pop_front();
        for (int dstStation = 0; dstStation < stationIXCount; dstStation ++) {
            if (transpose) {
                if (transportGraph.at(dstStation).at(currSrcStation) != -1) {
                    ADD_DST_STATION_AS_REACHABLE_IF_NEEDED();
                }
            }
            else {
                if (transportGraph.at(currSrcStation).at(dstStation) != -1) {
                    ADD_DST_STATION_AS_REACHABLE_IF_NEEDED();
                }
            }

        }
    }
    return reachables;
}

bool Graph::ContainsNode(const string &nodeName) {
    return stationIXMap.count(nodeName);
}

vector<string> Graph::GetNeighboursNames(const string &nodeName) {
    vector<string> names;
    for (auto &stationIx: transportGraph.at(stationIXMap[nodeName])) {
        names.push_back(GetStationNameByIX(stationIx));
    }
    return names;
}

vector<string> Graph::GetNodesNames() {
    vector<string> stations;
    for (auto &station: stationIXMap) {
        stations.push_back(station.first);
    }
    return stations;
}
