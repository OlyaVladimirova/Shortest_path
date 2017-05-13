//
// Created by Максим Бачинский on 27.04.17.
//

#ifndef WAYBIGWORK_GRAPH_H
#define WAYBIGWORK_GRAPH_H

using namespace std;
#include <map>
#include <vector>
#include <list>
#include <iostream>

// вершина

struct node {
    int id;

    node(int id) : id(id) {}
};

//
struct edge {
    node *pointA;
    node *pointB;
    int length;

    edge(node *pointA, node *pointB, int length) : pointA(pointA), pointB(pointB), length(length) {}
};


class Graph {
    typedef node *Node;
    typedef edge *Edge;

public:
    int getSize();

    vector<Node> nodes;
    vector<list<Edge>> adjacencyList;
    int numberOfNodes;

    Graph(std::istream &in);


};


#endif //WAYBIGWORK_GRAPH_H
