#include<iostream>
#include<cmath>
#include<cstring>
#define DEFAULT_SIZE 100
#define DEFAULT_INFINITY 1000000
using namespace std;

template<class E>
class SqStack
{
protected:
	int count;
	int maxSize;
	E *elems;
	E *now;//指向当前元素的指针 
	bool full() const;
	void Init(int size);
public:
	SqStack(int size = DEFAULT_SIZE);
	virtual ~SqStack();
	int StackLength();
	bool StackEmpty();
	E GetTop(E &x);
	void ClearStack();
    bool Push(E x);
	bool Pop(E &x);
	int GetCount(){ return count;}
	int GetMaxSize(){return maxSize;}
	
	void PrintAll();
	
};


template<class E>
bool SqStack<E>::full() const
{
	return count == maxSize;
}
//判满
template<class E>
void SqStack<E>::Init(int size)
{
	maxSize = size;
	count = 0;
	if (elems != NULL)
		delete[]elems;//释放
	elems = new E[maxSize];
	now=elems;
}
//初始化栈 最大元素个数为size

template<class E>
SqStack<E>::SqStack(int size)
{
	cout<<"A new stack is constructing.Stack Size:"<<size<<endl;
	elems = NULL;
	Init(size);
}
//构造函数

template<class E>
SqStack<E>::~SqStack()
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
E SqStack<E>::GetTop(E &x)
{
}

template <class E>
bool SqStack<E>::Push(E x)
{
	if (count > maxSize - 1)
		return false;
	else
	{
		now++;
		*now = x;
		count++;
		cout<<"push element:"<<x<<endl;
		return true;
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
		cout<<"pop element："<<*now<<endl; 
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

template<class E>
void SqStack<E>::PrintAll()
{
	cout<<"Now your stack status:";
	for(int i=1;i<=count;i++)
		cout<<elems[i]<<" ";
	cout<<endl;
}




int main()
{
	cout << "Please enter a expression:" << endl;
	string s;
	cin>>s;
	int len=s.size();
	SqStack<char> stack(len);
	for(int i=0;i<len;i++)
		stack.Push(s[i]);

}
