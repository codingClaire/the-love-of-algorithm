#include<iostream>
#include<cstdio>
#include<cstring>

template<class E,class W>
class Adjecent_Matrix_Directional_Network
{
public:
	void StatInDegree(const Adjecent_Matrix_Directional_Network<E, W>&net, int *indegree);
	int getEdgeNum() const;
	int getVertexNum() const;

private:
	int vexNum, edgeNum;
	int **matrix;
	E *elems;
	//ָ���־�����ָ��
	void DestroyHelp();

public:



};


