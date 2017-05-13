//
// Created by Максим Бачинский on 28.04.17.
//

#include "FordFW.h"

FordFW::FordFW(Graph *graph) : ShortestWayFinder(graph) {}

way FordFW::getShortestWay(node *a, node *b) {
    for (int i = 0; i < graph->getSize(); ++i) {
        if (graph->nodes[i] == a) {
            ways.push_back(0);
        } else {
            ways.push_back(INT_MAX);
        }
    }

    for (int j = 0; j < graph->getSize() - 1; ++j) {
        for (int i = 0; i < graph->getSize(); ++i) {
            for (auto &&item : graph->adjacencyList[i]) {
                relax(item);
            }
        }
    }

    return findWay(a, b);
}

void FordFW::relax(edge *e) {
    if (ways[e->pointA->id] + e->length < ways[e->pointB->id]) {
        ways[e->pointB->id] = ways[e->pointA->id] + e->length;
        prev[e->pointB->id] = e->pointA->id;
    }
}

ShortestWayFinder::way FordFW::findWay(node *a, node *b) {
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
