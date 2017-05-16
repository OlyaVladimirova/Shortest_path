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
	std::ifstream in("input.txt"); //Здесь хранится входной формат графа
	Graph object(in);  //Создаем граф, считывая из файла
	object.print_in_file();  //Здесь мы печатаем граф в файл "Graph.gv", который необходим для рисования графа
	system("circo Graph.gv -Tpng -o Graph.png");  //Этой командой мы "рисуем" граф.
												//Здесь circo - собственно сама программа, рисующая граф;
												//Graph.gv - текстовый файл с графом для рисования
												//Graph.png - рисунок графа

	FloydFW ford(&object);  //создаем объект для поиска кратчайшего пути (на примере алгоритма Флойда)
							//Как я понял на твоем компиляторе не важно какой класс здесь будет
							//FordFW, FloydFW или DeikstraFW, работать будет одинаково

	way test = ford.getShortestWay(&node(2), &node(1));  //Вызываем метод поиска кратчайшего пути 
														 //(из вершины 2 в верширну 1)

	ford.printShortestWay(test);	//Здесь мы добавляем кратчайший путь в граф, записанный в "Graph.gv"
									//и печатаем результат в новый файл "Graph_with_shortest_way.gv"

	system("circo Graph_with_shortest_way.gv -Tpng -o Graph_with_shortest_way.png"); //Этой командой мы "рисуем" 
																					//граф с кратчайшим путем по аналогии
	system("pause");
	return 0;
}