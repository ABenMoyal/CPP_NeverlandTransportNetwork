//
// Created by adirr on 14/05/2022.
//

#include "TransportNetwork.h"
#include <fstream>

void TransportNetwork::InboundOutboundHelper(const string &nodeName, bool transpose, const Terminal &terminal) {
    if (!ContainsNode(nodeName))
        throw runtime_error(nodeName + " does not exist in the current network.\n");
    string msgIfEmpty = transpose ? "no inbound travel" : "no outbound travel";
    terminal.ShowOutput("bus", busGraph.BFS(nodeName, transpose), msgIfEmpty);
    terminal.ShowOutput("tram", tramGraph.BFS(nodeName, transpose), msgIfEmpty);
    terminal.ShowOutput("sprinter", sprinterGraph.BFS(nodeName, transpose), msgIfEmpty);
    terminal.ShowOutput("rail", railGraph.BFS(nodeName, transpose), msgIfEmpty);
}

void TransportNetwork::inbound(const string &sourceNode, const Terminal &terminal) {
    InboundOutboundHelper(sourceNode, false, terminal);
}

void TransportNetwork::outbound(const string &destNode, const Terminal &terminal) {
    InboundOutboundHelper(destNode, true, terminal);
}

bool TransportNetwork::ContainsNode(const string &nodeName) {
    return (busGraph.ContainsNode(nodeName) || tramGraph.ContainsNode(nodeName) ||
            sprinterGraph.ContainsNode(nodeName) || railGraph.ContainsNode(nodeName));
}

Graph &TransportNetwork::GetGraphByVehicle(const string &vehicleName) {
    if (vehicleName == "bus") return busGraph;
    else if (vehicleName == "tram") return tramGraph;
    else if (vehicleName == "sprinter") return sprinterGraph;
    else if (vehicleName == "rail") return railGraph;
    else
        throw runtime_error("Error on TransportNetwork::GetGraphByVehicle: unknown vehicle name (" + vehicleName + ")");
}

void TransportNetwork::uniExpress(const string &sourceNode, const string &destNode, const Terminal &terminal) {
    // TODO: after we have Diakstra
}

void TransportNetwork::multiExpress(const string &sourceNode, const string &destNode, const Terminal &terminal) {
    // TODO: after we have Diakstra
}

void TransportNetwork::print(const string &outputFileName) {
    // TODO: check after we have Graph: adir
    set<string>&& allNodes = GetAllNodes();
    ofstream outputFile(outputFileName);
    for(const string& nodeName: allNodes){
        vector<string>&& neighbours = busGraph.GetNeighboursNames(nodeName);
        outputFile << nodeName << ": ";
        for(const string& neighbour: neighbours) outputFile<<neighbour<<"(bus), ";
        neighbours = tramGraph.GetNeighboursNames(nodeName);
        for(const string& neighbour: neighbours) outputFile<<neighbour<<"(tram), ";
        neighbours = sprinterGraph.GetNeighboursNames(nodeName);
        for(const string& neighbour: neighbours) outputFile<<neighbour<<"(sprinter), ";
        neighbours = railGraph.GetNeighboursNames(nodeName);
        for(const string& neighbour: neighbours) outputFile<<neighbour<<"(rail), ";
    }
}

set<string> TransportNetwork::GetAllNodes() {
    set<string> allNodes;
    for(const string& nodeName: busGraph.GetNodesNames()) allNodes.insert(nodeName);
    for(const string& nodeName: tramGraph.GetNodesNames()) allNodes.insert(nodeName);
    for(const string& nodeName: sprinterGraph.GetNodesNames()) allNodes.insert(nodeName);
    for(const string& nodeName: railGraph.GetNodesNames()) allNodes.insert(nodeName);
    return allNodes;
}
