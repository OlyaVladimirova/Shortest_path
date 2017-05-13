//
// Created by Максим Бачинский on 27.04.17.
//

#include "DeikstraFW.h"

DeikstraFW::DeikstraFW(Graph *graph) : ShortestWayFinder(graph) {

}

way DeikstraFW::getShortestWay(node *a, node *b) {
    for (int i = 0; i < graph->getSize(); ++i) {
        isAlso.push_back(false);
        if (graph->nodes[i] == a) {
            ways.push_back(0);
        } else {
            ways.push_back(INT_MAX);
        }
    }

    for (int j = 0; j < graph->getSize(); ++j) {
        node *current = j == 0 ? a : findmin();
        for (auto &&item : graph->adjacencyList[current->id]) {
            relax(item);
        }
        isAlso[current->id] = true;
        if (current == b) {
            return findWay(a, b);
        }
    }

}

node *DeikstraFW::findmin() {
    int minWay = INT_MAX;
    node *min;

    for (int i = 0; i < graph->getSize(); ++i) {
        if (ways[i] < minWay && !isAlso[i]) {
            minWay = ways[i];
            min = graph->nodes[i];
        }
    }

    return min;
}

void DeikstraFW::relax(edge *e) {
    if (!isAlso[e->pointB->id] && ways[e->pointA->id] + e->length < ways[e->pointB->id]) {
        ways[e->pointB->id] = ways[e->pointA->id] + e->length;
        prev[e->pointB->id] = e->pointA->id;
    }
}

ShortestWayFinder::way DeikstraFW::findWay(node *a, node *b) {
    node *end = b;
    way w;
    while (end != a) {
        w.first.push_front(end);
        end = graph->nodes[prev[end->id]];
    }
    w.first.push_front(a);
    w.second = ways[b->id];
    return w;

}


