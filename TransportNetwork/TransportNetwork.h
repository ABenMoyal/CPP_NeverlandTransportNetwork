//
// Created by adirr on 14/05/2022.
//

#ifndef HW2_TRANSPORTNETWORK_H
#define HW2_TRANSPORTNETWORK_H


#include "../Graph/Graph.h"
#include "../Terminal/Terminal.h"
#include <set>

class TransportNetwork {
private:
    Graph busGraph;
    Graph tramGraph;
    Graph sprinterGraph;
    Graph railGraph;
    void InboundOutboundHelper(const string& nodeName, bool transpose, const Terminal& terminal);
public:
    void inbound(const string& sourceNode, const Terminal& terminal);
    void outbound(const string& destNode, const Terminal& terminal);
    void uniExpress(const string& sourceNode, const string& destNode, const Terminal& terminal);
    void multiExpress(const string& sourceNode, const string& destNode, const Terminal& terminal);
    void print(const string& outputFileName);
    set<string> GetAllNodes();
    bool ContainsNode(const string& nodeName);
    Graph& GetGraphByVehicle(const string& vehicleName);
};


#endif //HW2_TRANSPORTNETWORK_H
