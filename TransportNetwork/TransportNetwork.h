//
// Created by adirr on 14/05/2022.
//

#ifndef HW2_TRANSPORTNETWORK_H
#define HW2_TRANSPORTNETWORK_H


#include "../Graph/Graph.h"
#include "../Terminal/Terminal.h"
#include <set>

typedef enum {BUS, TRAM, SPRINTER, RAIL} VehicleName;
class TransportNetwork {
private:
    Graph busGraph;
    Graph tramGraph;
    Graph sprinterGraph;
    Graph railGraph;
    void InboundOutboundHelper(const string& nodeName, bool transpose);
public:
    void inbound(const string& sourceNode);
    void outbound(const string& destNode);
    void uniExpress(const string& sourceNode, const string& destNode);
    void multiExpress(const string& sourceNode, const string& destNode);
    void print(const string& outputFileName);
    set<string> GetAllNodes();
    bool ContainsNode(const string& nodeName);
    Graph& GetGraphByVehicle(VehicleName vehicleName);
};


#endif //HW2_TRANSPORTNETWORK_H
