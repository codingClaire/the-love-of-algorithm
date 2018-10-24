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
	E *now;//ָ��ǰԪ�ص�ָ�� 
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
//����
template<class E>
void SqStack<E>::Init(int size)
{
	maxSize = size;
	count = 0;
	if (elems != NULL)
		delete[]elems;//�ͷ�
	elems = new E[maxSize];
	now=elems;
}
//��ʼ��ջ ���Ԫ�ظ���Ϊsize

template<class E>
SqStack<E>::SqStack(int size)
{
	cout<<"A new stack is constructing.Stack Size:"<<size<<endl;
	elems = NULL;
	Init(size);
}
//���캯��

template<class E>
SqStack<E>::~SqStack()
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
//����Ԫ��x

template <class E>
bool SqStack<E>::Pop(E &x)
{
	if (count == 0)
		return false;
	else
	{
		cout<<"pop element��"<<*now<<endl; 
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
