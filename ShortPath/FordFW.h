//
// Created by Максим Бачинский on 28.04.17.
//

#ifndef WAYBIGWORK_FORDFW_H
#define WAYBIGWORK_FORDFW_H


#include "FindWay.h"

class FordFW : public ShortestWayFinder {

public:
    FordFW(Graph *graph);

    virtual way getShortestWay(node *a, node *b) override;
	virtual void showShortestWay(node *a, node *b) override {}
private:

    vector<int> prev;
    vector<int> ways;

    void relax(edge *e);

    way findWay(node *a, node *b);


};


#endif //WAYBIGWORK_FORDFW_H
