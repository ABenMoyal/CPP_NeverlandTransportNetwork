//
// Created by adirr on 18/05/2022.
//

#ifndef HW2_GRAPHSTRUCTS_H
#define HW2_GRAPHSTRUCTS_H
#include <iostream>
#include <limits>

using namespace std;

struct DijkstraNode{
    string name;
    double d;  // used for Dijkstra
    DijkstraNode(const string& name, const double& d): name(name), d(d){}
    DijkstraNode(): d(std::numeric_limits<double>::infinity()){}
};
#endif //HW2_GRAPHSTRUCTS_H
