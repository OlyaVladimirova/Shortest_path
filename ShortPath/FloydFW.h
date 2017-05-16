

#include "FindWay.h"

class FloydFW : public ShortestWayFinder {
	typedef std::pair<int, int> p_type; //����� ������ ����� ���� � �������, ����� ������� �� ���� ���� ����� ��������������
	size_t size;  //������ ����� (���-�� ������)
	std::vector<std::vector<p_type>> matrix;  //������� ���������

	void alg_floyd();

	void getShortestWayMain(node *a, node *b, std::list<node *> &it);

public:

	FloydFW(Graph* graph);
	virtual way getShortestWay(node *a, node *b) override;
};



