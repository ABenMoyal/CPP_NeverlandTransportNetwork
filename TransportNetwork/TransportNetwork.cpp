//
// Created by adirr on 14/05/2022.
//

#include "TransportNetwork.h"
#include <fstream>

void TransportNetwork::InboundOutboundHelper(const string &nodeName, bool transpose) {
    print("out.txt");
    if (!ContainsNode(nodeName))
        throw runtime_error(nodeName + " does not exist in the current network.\n");
    string msgIfEmpty = transpose ? "no inbound travel" : "no outbound travel";
    Terminal::ShowOutput("bus", busGraph.BFS(nodeName, transpose), msgIfEmpty);
    Terminal::ShowOutput("tram", tramGraph.BFS(nodeName, transpose), msgIfEmpty);
    Terminal::ShowOutput("sprinter", sprinterGraph.BFS(nodeName, transpose), msgIfEmpty);
    Terminal::ShowOutput("rail", railGraph.BFS(nodeName, transpose), msgIfEmpty);
}

void TransportNetwork::inbound(const string &sourceNode) {
    InboundOutboundHelper(sourceNode, false);
}

void TransportNetwork::outbound(const string &destNode) {
    InboundOutboundHelper(destNode, true);
}

bool TransportNetwork::ContainsNode(const string &nodeName) {
    return (busGraph.ContainsNode(nodeName) || tramGraph.ContainsNode(nodeName) ||
            sprinterGraph.ContainsNode(nodeName) || railGraph.ContainsNode(nodeName));
}

Graph &TransportNetwork::GetGraphByVehicle(VehicleName vehicleName) {
    switch (vehicleName) {
        case BUS:
            return busGraph;
        case TRAM:
            return tramGraph;
        case SPRINTER:
            return sprinterGraph;
        case RAIL:
            return railGraph;
        default:
            throw runtime_error("Error on TransportNetwork::GetGraphByVehicle: unknown vehicle name (" +
                                to_string(int(vehicleName)) + ")");
    }
}

void uniExpressHelper(const string &vehicleName, const Graph &g, const string &sourceNode, const string &destNode, const int& stop_time) {
    try {
        map<string, double> &&dv_vector = g.Dijkstra(sourceNode, stop_time);
        Terminal::ShowOutput(vehicleName, dv_vector[destNode], "route unavailable");
    }
    catch (const exception &e) {
        Terminal::ShowOutput(vehicleName + ": " + (string) e.what());
    }
}

void TransportNetwork::uniExpress(const string &sourceNode, const string &destNode, const Config& config) {
    if (!ContainsNode(sourceNode)) {
        cout << sourceNode << " does not exist in the current network.\n";
        return;
    } else if (!ContainsNode(destNode)) {
        cout << destNode << " does not exist in the current network.\n";
        return;
    }
    uniExpressHelper("bus", busGraph, sourceNode, destNode, config.GetStopTimeByVehicle("bus"));
    uniExpressHelper("tram", tramGraph, sourceNode, destNode, config.GetStopTimeByVehicle("tram"));
    uniExpressHelper("sprinter", sprinterGraph, sourceNode, destNode, config.GetStopTimeByVehicle("sprinter"));
    uniExpressHelper("rail", railGraph, sourceNode, destNode, config.GetStopTimeByVehicle("rail"));
}

void TransportNetwork::multiExpress(const string &sourceNode, const string &destNode) {
    // TODO: after we have Diakstra
}

void TransportNetwork::print(const string &outputFileName) {
    set<string> &&allNodes = GetAllNodes();
    ofstream outputFile(outputFileName);

    for (const string &nodeName: allNodes) {
        vector<string> &&neighbours = busGraph.GetNeighboursNames(nodeName);
        outputFile << nodeName << ": ";
        for (const string &neighbour: neighbours) outputFile << neighbour << "(bus), ";
        neighbours = tramGraph.GetNeighboursNames(nodeName);
        for (const string &neighbour: neighbours) outputFile << neighbour << "(tram), ";
        neighbours = sprinterGraph.GetNeighboursNames(nodeName);
        for (const string &neighbour: neighbours) outputFile << neighbour << "(sprinter), ";
        neighbours = railGraph.GetNeighboursNames(nodeName);
        for (const string &neighbour: neighbours) outputFile << neighbour << "(rail), ";
        outputFile << '\n';
    }
    outputFile.close();
}

set<string> TransportNetwork::GetAllNodes() {
    set<string> allNodes;
    for (const string &nodeName: busGraph.GetNodesNames()) allNodes.insert(nodeName);
    for (const string &nodeName: tramGraph.GetNodesNames()) allNodes.insert(nodeName);
    for (const string &nodeName: sprinterGraph.GetNodesNames()) allNodes.insert(nodeName);
    for (const string &nodeName: railGraph.GetNodesNames()) allNodes.insert(nodeName);
    return allNodes;
}
