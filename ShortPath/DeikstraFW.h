//
// Created by Максим Бачинский on 27.04.17.
//

#ifndef WAYBIGWORK_DEIKSTRAFW_H
#define WAYBIGWORK_DEIKSTRAFW_H

#include "FindWay.h"

class DeikstraFW : public ShortestWayFinder {

public:
    DeikstraFW(Graph *graph);

    virtual way getShortestWay(node *a, node *b) override;

private:

    vector<bool> isAlso;
    vector<int> prev;
    vector<int> ways;

    node *findmin();

    void relax(edge *e);

    way findWay(node *a, node *b);

};


#endif //WAYBIGWORK_DEIKSTRAFW_H
