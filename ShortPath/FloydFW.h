

#include "FindWay.h"

class FloydFW : public ShortestWayFinder {
	typedef std::pair<int, int> p_type; //здесь храним длину пути и вершину, через который мы этот путь будем корректировать
	size_t size;  //размер графа (кол-во вершин)
	std::vector<std::vector<p_type>> matrix;  //матрица смежности

	void alg_floyd();

	void getShortestWayMain(node *a, node *b, std::list<node *> &it);

public:

	FloydFW(Graph* graph);
	virtual way getShortestWay(node *a, node *b) override;
};



