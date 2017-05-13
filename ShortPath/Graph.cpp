//
// Created by Максим Бачинский on 27.04.17.
//
#include "stdafx.h"
#include <fstream>
#include "Graph.h"

Graph::Graph(std::istream &in) {
    in >> numberOfNodes;
    adjacencyList.resize(numberOfNodes);

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

void Graph::print_in_file() const {
	ofstream fout("Graph.gv");
	fout << "digraph {\n";
	vector<list<Edge>>::const_iterator it = adjacencyList.begin();
	for (; it != adjacencyList.end(); ++it) {
		static list<Edge>::const_iterator it_list;
		it_list = it->begin();
		for (; it_list != it->end(); ++it_list) {
			fout << (*it_list)->pointA->id << "->" << (*it_list)->pointB->id
				<< "[label = " << (*it_list)->length << "]\n";
		}
	}
	fout << '}';
}
