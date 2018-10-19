#include<iostream>
using namespace std;

template<class E>
class SqStack
{
protected:
	int count;
	int maxSize;
	E *elems;
	E *now;

	bool full() const;
	void Init(int size);
public:
	SqStack(int size = DEFAULT_SIZE);
	virtual ~SqStack();
	int StackLength();
	bool StackEmpty();
	E GetTop(E &x);
	void ClearStack();
    StatusCode Push(E x);
	bool Pop(E &x);
};


template<class E>
bool SqStack<E>::full() const
{
	return count == maxSize;
}
//����

void Init(int size)
{
	maxSize = size;
	count = 0;
	if (elems != NULL)
		delete[]elems;//�ͷ�
	elems = new ElemType[maxSize];
}
//��ʼ��ջ ���Ԫ�ظ���Ϊsize

template<class E>
SqStack<E>::SqStack(int size)
{
	elems = NULL;
	Init(size);
}
//���캯��

template<class E>
SqStack<E>::~SqStack
{
	//if(elems!=NULL)
		delete[]elems;
}
//��������

template <class E>
int SqStack<E>::StackLength()
{
	return count;
}
//ջ�ĳ���

template <class E>
bool SqStack<E>::StackEmpty()
{
	if (count == 0)
		return false;
	return true;
}
//�ж�ջ�Ƿ�Ϊ��ջ

template <class E>
 SqStack<E>::GetTop(E &x)
{
}

template <class E>
StatusCode SqStack<E>::Push(E x)
{
	if (count > maxSize - 1)
		return OVER_FLOW;
	else
	{
		now++;
		*now = x;
		count++;
		return SUCCESS;
	}
}
//����Ԫ��x

template <class E>
bool SqStack<E>::Pop(E &x)
{
	if (count == 0)
		return false;
	else
	{
		x = *now;
		now--; 
		count--;
		return true;
	}

}
//ɾ��Ԫ��x

template<class E>
void SqStack<E>::ClearStack()
{
	count = 0;
}

int main()
{
	cout << "Please enter a expression:" << endl;
	char a[100];

}