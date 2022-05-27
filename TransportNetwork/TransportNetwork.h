//
// Created by adirr on 14/05/2022.
//

#ifndef HW2_TRANSPORTNETWORK_H
#define HW2_TRANSPORTNETWORK_H


#include "../Graph/Graph.h"
#include "../Terminal/Terminal.h"
#include "../Utils/Config.h"
#include <set>


class TransportNetwork {
private:
    Graph busGraph = {false, BUS};
    Graph tramGraph = {false, TRAM};
    Graph sprinterGraph = {false, SPRINTER};
    Graph railGraph = {false, RAIL};
    void InboundOutboundHelper(const string& nodeName, bool transpose);
public:
    void inbound(const string& sourceNode);
    void outbound(const string& destNode);
    void uniExpress(const string& sourceNode, const string& destNode, const Config& config);
    void multiExpress(const string& sourceNode, const string& destNode, const Config& config);
    void print(const string& outputFileName);
    set<string> GetAllNodes();
    bool ContainsNode(const string& nodeName);
    Graph& GetGraphByVehicle(VehicleName vehicleName);

    void BuildMergedGraph(Graph *mrgedGraph);
};


#endif //HW2_TRANSPORTNETWORK_H
