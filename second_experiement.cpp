#include<iostream>
#include<cmath>
#include<cstring>
#define DEFAULT_SIZE 100
#define DEFAULT_INFINITY 1000000
using namespace std;

template<class E>
class String
{
	char* ch;
	int length;
protected:
	
public:
	StrAssign(char* chars);
	StrCopy(S)
};


template<class E>
bool SqStack<E>::full() const
{
	return count == maxSize;
}

template<class E>
void SqStack<E>::Init(int size)
{
	maxSize = size;
	count = 0;
	if (elems != NULL)
		delete[]elems;// Õ∑≈
	elems = new E[maxSize];
	now = elems;
}