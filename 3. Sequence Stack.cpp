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
//判满

void Init(int size)
{
	maxSize = size;
	count = 0;
	if (elems != NULL)
		delete[]elems;//释放
	elems = new ElemType[maxSize];
}
//初始化栈 最大元素个数为size

template<class E>
SqStack<E>::SqStack(int size)
{
	elems = NULL;
	Init(size);
}
//构造函数

template<class E>
SqStack<E>::~SqStack
{
	//if(elems!=NULL)
		delete[]elems;
}
//析构函数

template <class E>
int SqStack<E>::StackLength()
{
	return count;
}
//栈的长度

template <class E>
bool SqStack<E>::StackEmpty()
{
	if (count == 0)
		return false;
	return true;
}
//判断栈是否为空栈

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
//插入元素x

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
//删除元素x

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