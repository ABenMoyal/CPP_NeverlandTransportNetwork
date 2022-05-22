//
// Created by adirr on 04/05/2022.
//

#include <set>
#include "Graph.h"
#include "list"
#include "GraphStructs.h"
#include "../Utils/Config.h"
#include <queue>

double INFINITY = std::numeric_limits<double>::infinity();

void Graph::AddStationToTransportGraph() {
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

void Graph::UpdateGraph(Edge &input) {
    ADD_NEW_STATION_TO_GRAPH_IF_NEEDED(input.src);
    ADD_NEW_STATION_TO_GRAPH_IF_NEEDED(input.dest);
    int srcIx = stationIXMap[input.src];
    int dstIx = stationIXMap[input.dest];
    if (transportGraph.at(srcIx).at(dstIx) > input.duration || transportGraph.at(srcIx).at(dstIx) == -1) {
        transportGraph.at(srcIx).at(dstIx) = input.duration;
    }
}

string Graph::GetStationNameByIX(int ix) const {
    for (auto &station: stationIXMap) {
        if (station.second == ix) return station.first;
    }
    // TODO: ERROR
    cout << "Graph::GetStationNameByIX ix not found but sent from vector " << endl;
    exit(1);

}

#define ADD_DST_STATION_AS_REACHABLE_IF_NEEDED() { \
    string dstName =  GetStationNameByIX(dstStation); \
    if(dstStation==currSrcStation || srcIx == dstStation) continue;                \
    if (!contains(reachables, dstName)) {          \
        reachables.push_back(dstName); \
        queue.push_back(dstStation); \
    }\
}

vector<string> Graph::BFS(const string &source, bool transpose) {
    vector<string> reachables;
    list<int> queue;
    if (!ContainsNode(source)) return {};
    int srcIx = stationIXMap[source];

    queue.push_back(srcIx);
    int currSrcStation;
    while (!queue.empty()) {
        currSrcStation = queue.front();
        queue.pop_front();
        for (int dstStation = 0; dstStation < stationIXCount; dstStation++) {
            if (transpose) {
                if (transportGraph.at(dstStation).at(currSrcStation) != -1) {
                    ADD_DST_STATION_AS_REACHABLE_IF_NEEDED();
                }
            } else {
                if (transportGraph.at(currSrcStation).at(dstStation) != -1) {
                    ADD_DST_STATION_AS_REACHABLE_IF_NEEDED();
                }
            }
        }
    }
    return reachables;
}

bool Graph::ContainsNode(const string &nodeName) const {
    return stationIXMap.count(nodeName);
}

vector<string> Graph::GetNeighboursNames(const string &nodeName) const {
    vector<string> names;
    if (!ContainsNode(nodeName)) return {};
    for (int i = 0; i < stationIXCount; i++) {
        if (transportGraph.at(stationIXMap.at(nodeName)).at(i) != -1)
            names.push_back(GetStationNameByIX(i));
    }
    return names;
}

vector<string> Graph::GetNodesNames() const {
    vector<string> stations;
    for (auto &station: stationIXMap) {
        stations.push_back(station.first);
    }
    return stations;
}

bool IsSameStation(const string &node1, const string &node2) {
    string stationName1 = node1.substr(0, node1.rfind('_'));
    string stationName2 = node2.substr(0, node2.rfind('_'));
    return stationName1 == stationName2;
}

int GetStopTime(const string &current, const string &neighbour, const string &destNode, const Graph& graph,
                const Config &config) {
    if (graph.IsMergedGraph() && IsSameStation(current, neighbour)) return config.GetTransitTimeByStationName(current);
    return neighbour==destNode? 0: config.GetStopTimeByVehicle(graph.GetVehicleName());
}

map<string, double> Graph::Dijkstra(const string &sourceNode, const string &destNode, const Config& config) const {
    if (!ContainsNode(sourceNode)) throw runtime_error("route unavailable");

    // Initialize dv_vector & minHeap
    map<string, DijkstraNode *> nodes;
    vector<DijkstraNode *> vectorHeap;
    DijkstraNode *node;
    for (const string &nodeName: GetNodesNames()) {
        node = new DijkstraNode(nodeName, nodeName == sourceNode ? 0 : INFINITY);
        vectorHeap.push_back(node);
        nodes[nodeName] = node;
    }

    DijkstraNode *current;
    int currentIndex, neighbourIndex, edgeWeight;
    while (!vectorHeap.empty()) {
        // EXTRACT-MIN
        sort(vectorHeap.begin(), vectorHeap.end(), [](DijkstraNode *a, DijkstraNode *b) { return a->d > b->d; });
        current = vectorHeap[vectorHeap.size() - 1];
        vectorHeap.pop_back();

        // UPDATE NEIGHBOURS
        currentIndex = stationIXMap.at(current->name);
        for (const string &neighbour: GetNeighboursNames(current->name)) {
            neighbourIndex = stationIXMap.at(neighbour);
            edgeWeight = transportGraph.at(currentIndex).at(neighbourIndex);
            int extraWeight = GetStopTime(current->name, neighbour, destNode, *this, config);
            if (nodes[neighbour]->d > nodes[current->name]->d + edgeWeight + extraWeight) {
                nodes[neighbour]->d = nodes[current->name]->d + edgeWeight + extraWeight;
            }
        }
    }

    map<string, double> dv_vector;
    for (const auto &nameToNodePair: nodes) {
        dv_vector.insert({nameToNodePair.first, nameToNodePair.second->d});
        delete nameToNodePair.second;
    }

    // TODO: Delete after validation
//    for(auto node: dv_vector) cout << node.first << ": " << node.second << endl;
    return dv_vector;
}


// if SameStation() && GetVehicleFromStationName(source) != GetVehicleFromStationName(neighbour);
