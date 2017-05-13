
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Graph.h"
#include "FloydFW.h"
#include "DeikstraFW.h"
#include "FordFW.h"

typedef pair<list<node *>, int> way;

int main()
{
	std::ifstream in("input.txt");
	std::ifstream in_m("input_matrix.txt");
	Graph object(in);
	object.print_in_file();
	FloydFW ford(&object);
	way test = ford.getShortestWay(&node(2), &node(1));
	ford.printShortestWay(test);
	system("pause");
	return 0;
}