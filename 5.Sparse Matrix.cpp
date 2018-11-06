#include<iostream>
#include<cstdio>
using namespace std;

#define INF 1000000


template<class E> class SparseMatrix;

template<class E> class Trituple 
{
	friend class SparseMatrix <E>
private:
	int row, col;	  //非零元素行号/列号
	E value;     //非零元素的值
}


template<class E>class SparseMatrix
{
	int Rows, Cols, Terms;//行/列/非零元素数
	Trituple<E> smArray[MaxTerms];//三元组表
public:                                
	SparseMatrix(int MaxRow, int Maxcol);
	SparseMatrix<Type>& Transpose(SparseMatrix<E>&);//转置   
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
	/* 二阶算法*/
	int q = 0;//指向新的矩阵三元组
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

	/*一阶算法*/
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
		//q如何计算？
		int q = x[from.smArray[i].col];
		to.smArray[q].row = from.smArray[i].col;
		to.smArray[q].col = from.smArray[i].row;
		to.smArray[q].value = from.smArray[i].value;
		x[from.smArray[i].col]++;//房间号加1 防止重复放入同一房间

	}
	delete []x;
	delete []y;
	return to;
}

