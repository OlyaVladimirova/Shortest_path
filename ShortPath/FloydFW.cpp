

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "FloydFW.h"

const int infinity = INT_MAX; 
typedef pair<list<node *>, int> way;

void FloydFW::alg_floyd() {
	int x;
	for (size_t k = 0; k < size; ++k) {
		for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j < size; ++j) {
				if ((k == i) || (k == j) || (i == j)
					|| (matrix[i][k].first == infinity) || (matrix[k][j].first == infinity)) continue;
				if (matrix[i][j].first >= (matrix[i][k].first + matrix[k][j].first)) {
					x = (matrix[i][k].first + matrix[k][j].first);
					matrix[i][j].first = x;
					matrix[i][j].second = k;
				}
			}
		}
	}
}

void FloydFW::getShortestWayMain(node *a, node *b, std::list<node *> &it) {
	if ((matrix[a->id][b->id].second == b->id) || (matrix[a->id][b->id].second == a->id)) return;


	if (matrix[a->id][b->id].second != a->id) {

		getShortestWayMain(a, &node(matrix[a->id][b->id].second), it);
		node* help = new node(matrix[a->id][b->id].second);
		it.push_back(help);
		getShortestWayMain(&node(matrix[a->id][b->id].second), b, it);

	}
}

FloydFW::FloydFW(Graph* graph)
	:ShortestWayFinder(graph)
{
	size = graph->getSize();
	matrix.resize(size);
	for (size_t i = 0; i < size; ++i) matrix[i].resize(size);

	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < size; ++j) {
			if (i == j) matrix[i][j].first = 0;
			else
				matrix[i][j].first = infinity;
			matrix[i][j].second = i;
		}
	}

	for (auto i = 0; i != size; ++i) {
		for (auto list = graph->adjacencyList[i].begin(); list != graph->adjacencyList[i].end(); ++list)
			matrix[(*list)->pointA->id][(*list)->pointB->id].first = (*list)->length;
	}

	alg_floyd();
}

way FloydFW::getShortestWay(node *a, node *b)  {
	std::list<node *> it;
	if (matrix[a->id][b->id].first == infinity) {
		std::cout << "There is no path from " << a->id << " to " << b->id << std::endl;
		return way(it, 0);
	}
	else {
		it.push_back(a);
		getShortestWayMain(a, b, it);
		it.push_back(b);
		int length = 0;
		auto reserve = it.begin();
		auto help = it.begin();
		help++;
		while (help != it.end()) {
			auto i = graph->adjacencyList[(*reserve)->id].begin();
			while ((*i)->pointB->id != (*help)->id) i++;
			length += (*i)->length;
			++reserve;
			++help;
		}
		return way(it, length);
	}
}