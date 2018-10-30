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
	E GetTop();
	E GetElem(int i);
	void ClearStack();
    bool Push(E x);
	bool Pop();
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
		return true;
	return false;
}
//�ж�ջ�Ƿ�Ϊ��ջ

template <class E>
E SqStack<E>::GetTop()
{
	return *now;
}

template <class E>
E SqStack<E>::GetElem(int i)
{
	return *(now-count+i+1);
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
bool SqStack<E>::Pop()
{
	if (count == 0)
		return false;
	else
	{
		cout<<"pop element��"<<*now<<endl; 
		//x = *now;
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

int signvalue(char a)
{
	if(a=='+'||a=='-') return 1;
	if(a=='*'||a=='/') return 2;
	if(a=='^') return 3;	
}//���������������Ӧֵ���������ȼ����� 

char cal(char a,int b,int c)
{
	if(a=='+') return b+c;
	else if(a=='-') return b-c;
	else if(a=='*') return b*c;
	else if(a=='/') return b/c; 
//	else if(a=='^') return (int)pow((float)b,(float)c);
} 

int main()
{
	cout << "Please enter a expression:" << endl;
	string s;
	cin>>s;
	int len=s.size();
	SqStack<char> stack(len+5),signstack(len+5); //�ַ�����ջ 
	for(int i=0;i<len;i++)
	{
		if(s[i]>='0'&&s[i]<='9')
			stack.Push(s[i]);			
		else if(s[i]=='(') 
			signstack.Push(s[i]);
		else if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='^')
		{
			if(signstack.StackEmpty()==true)
				signstack.Push(s[i]);
			else if(s[i+1]==')'||signstack.GetTop()=='(')
			{
				signstack.Push(s[i]);	
			} 
			else if(signvalue(signstack.GetTop())<signvalue(s[i]))//����һ�����ȼ��� 
			{
				//stack.Push(s[i+1]);
				//stack.Push(s[i]);
				signstack.Push(s[i]); 
			}
			else if(signvalue(signstack.GetTop())>=signvalue(s[i]))
			{
				stack.Push(signstack.GetTop());
				signstack.Pop();
				signstack.Push(s[i]);
			}
			
		}
		else if(s[i]==')')
		{
			
			while(signstack.GetTop()!='(')
			{
				stack.Push(signstack.GetTop());
				signstack.Pop();
			}	 
			signstack.Pop();
		}
	stack.PrintAll();
	signstack.PrintAll();
	}
	while(signstack.StackEmpty()==false)
	{
		stack.Push(signstack.GetTop());
		signstack.Pop();
	}	
	stack.PrintAll();
	signstack.PrintAll();
	//���Ͻ����ʽ ��Ϊ������+������+���������ʽ
	
	//for(int i=0;i<len;i++)
	//	cout<<stack.GetElem(i)<<endl;
	int reslen=stack.GetCount();
	SqStack<int> res(reslen);
	for(int i=0;i<reslen;i++)
	{
		if(stack.GetElem(i)>='0'&&stack.GetElem(i)<='9')
			res.Push(stack.GetElem(i)-'0');
		else
		{
			int cnt=res.GetCount();
			int num1=res.GetTop();
			res.Pop();
			int num2=res.GetTop();
			res.Pop();
			res.Push(cal(stack.GetElem(i),num2,num1));
		}
		res.PrintAll();
	}
	cout<<res.GetTop()<<endl;
return 0;
}
//5+6*(4+7)
//5+6*4-((3+5)*2+6)
//5+4^(2+3)
