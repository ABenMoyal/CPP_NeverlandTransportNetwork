//
// Created by adirr on 14/05/2022.
//

#include "TransportNetwork.h"
#include <list>
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

void uniExpressHelper(const string &vehicleName, const Graph &g, const string &sourceNode, const string &destNode,
                      const Config &config) {
    try {
        map<string, double> &&dv_vector = g.Dijkstra(sourceNode, destNode, config);
        Terminal::ShowOutput(vehicleName, dv_vector[destNode], "route unavailable");
    }
    catch (const exception &e) {
        Terminal::ShowOutput(vehicleName + ": " + (string) e.what());
    }
}

void TransportNetwork::uniExpress(const string &sourceNode, const string &destNode, const Config &config) {
    if (!ContainsNode(sourceNode)) {
        cout << sourceNode << " does not exist in the current network.\n";
        return;
    } else if (!ContainsNode(destNode)) {
        cout << destNode << " does not exist in the current network.\n";
        return;
    }
    uniExpressHelper("bus", busGraph, sourceNode, destNode, config);
    uniExpressHelper("tram", tramGraph, sourceNode, destNode, config);
    uniExpressHelper("sprinter", sprinterGraph, sourceNode, destNode, config);
    uniExpressHelper("rail", railGraph, sourceNode, destNode, config);
}

void multiExpressHelper(const Graph &g, const string &sourceNode, const string &destNode,const Config &config) {
    try {
        map<string, double> &&dv_vector_from_bus = g.Dijkstra(sourceNode+ "_bus", destNode, config);
        map<string, double> &&dv_vector_from_tram = g.Dijkstra(sourceNode+ "_tram", destNode, config);
        map<string, double> &&dv_vector_from_rail = g.Dijkstra(sourceNode+ "_rail", destNode, config);
        map<string, double> &&dv_vector_from_sprinter = g.Dijkstra(sourceNode+ "_sprinter", destNode, config);
        initializer_list<double> optionalDv = {dv_vector_from_bus[destNode+"_bus"], dv_vector_from_bus[destNode+"_tram"],
            dv_vector_from_bus[destNode+"rail"], dv_vector_from_bus[destNode+"_sprinter"],
            dv_vector_from_tram[destNode+"_bus"], dv_vector_from_tram[destNode+"_tram"],
            dv_vector_from_tram[destNode+"_rail"], dv_vector_from_tram[destNode+"_sprinter"],
            dv_vector_from_rail[destNode+"_bus"], dv_vector_from_rail[destNode+"_tram"],
            dv_vector_from_rail[destNode+"_rail"], dv_vector_from_rail[destNode+"_sprinter"],
            dv_vector_from_sprinter[destNode+"_bus"], dv_vector_from_sprinter[destNode+"_tram"],
            dv_vector_from_sprinter[destNode+"_rail"], dv_vector_from_sprinter[destNode+"_sprinter"]};
        Terminal::ShowOutput("Shortest time", min(optionalDv), "route unavailable");
    }
    catch (const exception &e) {
        Terminal::ShowOutput("Shortest time: " + (string) e.what());
    }
}

void TransportNetwork::BuildMergedGraph(Graph *mergedGraph) {
    vector<Graph> allGraphs {busGraph, tramGraph, sprinterGraph, railGraph};
    for (Graph currentGraph: allGraphs) {
        for (string nodeName: currentGraph.GetNodesNames()){
            for (string neighbor: currentGraph.GetNeighboursNames(nodeName)) {
                Edge newEdge;
                newEdge.src = nodeName + "_" + currentGraph.GetVehicleNameString();
                newEdge.dest = neighbor + "_" + currentGraph.GetVehicleNameString();
                try{
                    newEdge.duration = currentGraph.GetDuration(nodeName, neighbor);
                } catch (exception &e) {
                    cout << "Error: " << e.what() << endl;
                    exit(1);
                }
                mergedGraph->UpdateGraph(newEdge);
            }
        }
    }
    int srcIx = 0;
    string srcName = "";
    string destName = "";
    for (vector<int> srcNode: mergedGraph->GetTransportGraph()) {
        for (int destIx: srcNode) {
            try {
                srcName = mergedGraph->GetStationNameByIX(srcIx);
                destName = mergedGraph->GetStationNameByIX(destIx);
            } catch (exception &e) {
                cout << "Error: " << e.what() << endl;
                exit(1);
            }
            if (Graph::IsSameStation(srcName, destName)){
                Edge newEdge;
                newEdge.src = srcName;
                newEdge.dest = destName;
                newEdge.duration = 0;
                mergedGraph->UpdateGraph(newEdge);
            }
        }
        srcIx++;
    }
}

void TransportNetwork::multiExpress(const string &sourceNode, const string &destNode, const Config &config) {
    if (!ContainsNode(sourceNode)) {
        cout << sourceNode << " does not exist in the current network.\n";
        return;
    } else if (!ContainsNode(destNode)) {
        cout << destNode << " does not exist in the current network.\n";
        return;
    }
    Graph* mergedGraph = new Graph(true);
    BuildMergedGraph(mergedGraph);
    multiExpressHelper(mergedGraph, sourceNode, destNode, config);
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
