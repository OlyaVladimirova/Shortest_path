//
// Created by Максим Бачинский on 27.04.17.
//

#ifndef WAYBIGWORK_FINDWAY_H
#define WAYBIGWORK_FINDWAY_H

#include "Graph.h"
#include <string>
#include <fstream>
#include <utility>

using namespace std;

class ShortestWayFinder {

public:

	typedef pair<list<node *>, int> way;
    virtual way getShortestWay(node *a, node *b) = 0;

	ShortestWayFinder(Graph *graph) : graph(graph) {}
	//ShortestWayFinder() = default;

	void printShortestWay(way shortest_way) {
		if (shortest_way.first.empty()) {
			cout << "Way doesn`t exist\n";
			return;
		}
		ifstream fin("Graph.gv");
		ofstream fout("Graph_with_shortest_way.gv");
		while (fin.peek() != '}') {
			static char tmp;
			tmp = fin.get();
			fout << tmp;
		}
		list<node*>::const_iterator it = shortest_way.first.begin();
		list<node*>::const_iterator it_next = it;
		it_next++;
		for (; it_next != shortest_way.first.end(); ++it, ++it_next) {
			fout << (*it)->id << "->" << (*it_next)->id << "[color = red]\n";
		}
		fout << '}';
	}

protected:
    Graph* graph;
};



#endif //WAYBIGWORK_FINDWAY_H
