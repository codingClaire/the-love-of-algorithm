#include<iostream>
#include<cstdio>
using namespace std;

#define INF 1000000


template<class E> class SparseMatrix;

template<class E> class Trituple 
{
	friend class SparseMatrix <E>
private:
	int row, col;	  //����Ԫ���к�/�к�
	E value;     //����Ԫ�ص�ֵ
}


template<class E>class SparseMatrix
{
	int Rows, Cols, Terms;//��/��/����Ԫ����
	Trituple<E> smArray[MaxTerms];//��Ԫ���
public:                                
	SparseMatrix(int MaxRow, int Maxcol);
	SparseMatrix<Type>& Transpose(SparseMatrix<E>&);//ת��   
}

template<class E>
{

}



template<class E>
SparseMatrix<E>& SparseMatrix::Transpose(SparseMatrix<E>& from,SparseMatrix<E>& to)
{
	to.rows = from.cols;
	to.cols = from.rows;
	to.terms = from.terms;
	/* �����㷨*/
	int q = 0;//ָ���µľ�����Ԫ��
	if (from.Terms > 0)
	{
		for (int i = 0; i <from.Cols; i++)
		{
			for (int j; j < from.Terms - 1; j++)
			{
				if (from.smArray[j].col == i)
				{
					to.smArray[q].row = from.smArray[j].col;
					to.smArray[q].col = from.smArray[j].row;
					to.smArray[q].value = from.smArray[j].value;
					q++;
				}
			}
		}
	}*/

	/*һ���㷨*/
	int *x = new int[from.Cols];
	int *y = new int[from.Cols];
	for (int i = 0; i < from.Cols; i++)
		y[i] = 0;
	for (int i = 0; i < from.Terms; i++)
		y[from.smArray.col]++;
	x[0] = 0;
	for (int i = 1; i < from.Cols; i++)
		x[i] = x[i - 1] + y[i - 1];
	for (int i = 0; i < from.Terms - 1; i++)
	{
		//q��μ��㣿
		int q = x[from.smArray[i].col];
		to.smArray[q].row = from.smArray[i].col;
		to.smArray[q].col = from.smArray[i].row;
		to.smArray[q].value = from.smArray[i].value;
		x[from.smArray[i].col]++;//����ż�1 ��ֹ�ظ�����ͬһ����

	}
	delete []x;
	delete []y;
	return to;
}

