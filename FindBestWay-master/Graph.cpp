//
// Created by Максим Бачинский on 27.04.17.
//

#include "Graph.h"

Graph::Graph(std::istream &in) {
    in >> numberOfNodes;
    adjacencyList = vector(numberOfNodes);

    for (int i = 0; i < numberOfNodes; ++i) {
        node *n = new node(i);
        nodes.push_back(n);
    }

    for (int j = 0; j < numberOfNodes; ++j) {
        int number;
        in >> number;
        for (int i = 0; i < number; ++i) {
            int pointBId, length;
            in >> pointBId >> length;
            edge *e = new edge(nodes[j], nodes[pointBId], length);
            adjacencyList[j].push_back(e);
        }
    }
}

int Graph::getSize() {
    return numberOfNodes;
}
