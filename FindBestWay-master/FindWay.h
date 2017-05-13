//
// Created by Максим Бачинский on 27.04.17.
//

#ifndef WAYBIGWORK_FINDWAY_H
#define WAYBIGWORK_FINDWAY_H

#include "Graph.h"
#include <utility>

using namespace std;

class ShortestWayFinder {

public:
    virtual way getShortestWay(node *a, node *b) = 0;

    ShortestWayFinder(Graph *graph) : graph(graph) {}

    typedef pair<list<node *>, int> way;
protected:
    Graph* graph;


};

#endif //WAYBIGWORK_FINDWAY_H
