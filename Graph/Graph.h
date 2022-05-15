//
// Created by adirr on 04/05/2022.
//

#ifndef HW2_GRAPH_H
#define HW2_GRAPH_H

#include <iostream>
#include <vector>

using namespace std;

// TODO: implement Graph(by matrix) with upload & BFS & whatever needed: shani
class Graph {
private:

public:
    vector<string> BFS(const string &source, bool transpose = false);
    bool ContainsNode(const string &nodeName);
    vector<string> GetNeighboursNames(const string& nodeName);
    vector<string> GetNodesNames();
};


#endif //HW2_GRAPH_H
