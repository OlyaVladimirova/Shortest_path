// ShortPath.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <ctime>
#include "FindWay.h"

const int infinity = INT_MAX;  //обозначение несуществующего пути из одной вершины в другую

class FloydFW : public ShortestWayFinder {
	typedef std::pair<int, int> p_type; //здесь храним длину пути и вершину, через который мы этот путь будем корректировать
	size_t size;  //размер графа (кол-во вершин)
	std::vector<std::vector<p_type>> matrix;  //матрица смежности

	void alg_floyd() {
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

	void show_short_path_main(int x, int y) {
		if ((matrix[x][y].second == y) || (matrix[x][y].second == x)) return;


		if (matrix[x][y].second != x) {

			show_short_path_main(x, matrix[x][y].second);
			std::cout << matrix[x][y].second << " -> ";
			show_short_path_main(matrix[x][y].second, y);

		}
	}

	void get_short_path_main(node *a, node *b, std::list<node *> &it) {
		if ((matrix[a->id][b->id].second == b->id) || (matrix[a->id][b->id].second == a->id)) return;


		if (matrix[a->id][b->id].second != a->id) {

			get_short_path_main(a, &node(matrix[a->id][b->id].second), it);
			node* help = new node(matrix[a->id][b->id].second);
			it.push_back(help);
			get_short_path_main(&node(matrix[a->id][b->id].second), b, it);

		}
	}

public:

	FloydFW(Graph* graph)
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

	//конструктор графа через ввод из файла
	FloydFW(std::ifstream &in) {
		in >> size;

		/*matrix = new p_type*[size];
		for (size_t i = 0; i < size; ++i) matrix[i] = new p_type[size];*/
		matrix.resize(size);
		for (size_t i = 0; i < size; ++i) matrix[i].resize(size);

		for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j < size; ++j) {
				in >> matrix[i][j].first;
				matrix[i][j].second = i;
			}
		}

		alg_floyd();
	}

	//конструктор графа, генерирующий рандомный граф размером size
	//с вероятностью появления веса длиной бесконечность = 1/cnance_infinity
	//с диапазоном весов = range_of_weights
	FloydFW(size_t size, size_t chance_infinity = 3, int range_of_weights = 10)
	:size(size)
	{
		srand(time(NULL));
		size_t chance;
		/*matrix = new p_type*[size];
		for (size_t i = 0; i < size; ++i) matrix[i] = new p_type[size];*/

		matrix.resize(size);
		for (size_t i = 0; i < size; ++i) matrix[i].resize(size);

		for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j < size; ++j) {
				if (i == j) {
					matrix[i][j].first = 0;
					matrix[i][j].second = i;
				}
				else {
					chance = rand() % chance_infinity;
					if (chance) {
						matrix[i][j].first = rand() % range_of_weights;
						/*chance = rand() % 2;
						if (chance) matrix[i][j].first = rand() % range_of_weights;
						else matrix[i][j].first = -(rand() % range_of_weights);*/
					}
					else
						matrix[i][j].first = infinity;
					matrix[i][j].second = i;
				}
			}
		}

		alg_floyd();
	}

	//вывод матрицы на экран
	void show() {
		for (size_t i = 0; i < size; ++i) {
			for (size_t j = 0; j < size; ++j) {
				if (matrix[i][j].first == infinity)
					std::cout << "oo" << "," << matrix[i][j].second << "\t\t";
				else
					std::cout << matrix[i][j].first << "," << matrix[i][j].second << "\t\t";
			}
			std::cout << std::endl;
		}
	}

	virtual void showShortestWay(node *a, node *b) override {
		if (matrix[a->id][b->id].first == infinity) std::cout << "There is no path from " << a->id << " to " << b->id << std::endl;
		else {
			std::cout << a->id << " -> ";
			show_short_path_main(a->id, b->id);
			std::cout << b->id << '\n';
		}
	}

	virtual way getShortestWay(node *a, node *b) override { 
		std::list<node *> it;
		if (matrix[a->id][b->id].first == infinity) {
			std::cout << "There is no path from " << a->id << " to " << b->id << std::endl;
			return way(it, 0);
		}
		else {
			it.push_back(a);
			get_short_path_main(a, b, it);
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
};



