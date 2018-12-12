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
	int count;//ջ�д洢Ԫ�ظ���
	int maxSize;//ջ�����洢��
	E *elems;//elems����
	E *now;//ָ��ǰԪ�ص�ָ�� 
	bool full() const;//����
	void Init(int size);//��ʼ��
public:
	SqStack(int size = DEFAULT_SIZE);
	virtual ~SqStack();
	int StackLength();//ջ�ĳ���
	bool StackEmpty();//�ж�ջ�Ƿ��
	E GetTop();//ȡջ��Ԫ��
	E GetElem(int i);//���ص�i��ջ�ڵ�Ԫ��
	void ClearStack();//���ջ
	bool Push(E x);//Ԫ�ؽ�ջ
	bool Pop();//Ԫ�س�ջ
	int GetCount() { return count; }//ջ��Ԫ�ظ���
	int GetMaxSize() { return maxSize; }//ջ�����洢��

	void PrintAll();//��ӡջ��Ԫ��

};


template<class E>
bool SqStack<E>::full() const
{
	return count == maxSize;
}

template<class E>
void SqStack<E>::Init(int size)
{//��ʼ��ջ ���Ԫ�ظ���Ϊsize
	maxSize = size;
	count = 0;
	if (elems != NULL)
		delete[]elems;//�ͷ�
	elems = new E[maxSize];
	now = elems;
}

template<class E>
SqStack<E>::SqStack(int size)
{
	cout << "һ����ջ��������.ջ��СΪ:" << size << endl;
	elems = NULL;
	Init(size);
}

template<class E>
SqStack<E>::~SqStack()
{
	delete[]elems;
}

template <class E>
int SqStack<E>::StackLength()
{
	return count;
}

template <class E>
bool SqStack<E>::StackEmpty()
{
	return count == 0;
}

template <class E>
E SqStack<E>::GetTop()
{
	return *now;
}

template <class E>
E SqStack<E>::GetElem(int i)
{
	return *(now - count + i + 1);
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
		cout << "push element:" << x << endl;
		return true;
	}
}

template <class E>
bool SqStack<E>::Pop()
{
	if (count == 0)
		return false;
	else
	{
		cout << "pop element��" << *now << endl;
		//x = *now;
		now--;
		count--;
		return true;
	}

}

template<class E>
void SqStack<E>::ClearStack()
{
	count = 0;
}

template<class E>
void SqStack<E>::PrintAll()
{
	for (int i = 1; i <= count; i++)
		cout << elems[i] << " ";
	cout << endl;
}

int signvalue(char a)
{
	if (a == '+' || a == '-') return 1;
	if (a == '*' || a == '/') return 2;
	if (a == '^') return 3;
}//���������������Ӧֵ���������ȼ����� 

char cal(char a, int b, int c)
{
	if (a == '+') return b + c;
	else if (a == '-') return b - c;
	else if (a == '*') return b*c;
	else if (a == '/') return b / c;
}

int main()
{
	cout << "Please enter a expression:" << endl;
	string s;
	cin >> s;
	int len = s.size();
	SqStack<char> stack(len + 5), signstack(len + 5); 
	//�ַ�����ջ,stack�洢�������ֽ����signstack�洢���� 
	for (int i = 0; i<len; i++)
	{
		if (s[i] >= '0'&&s[i] <= '9')//���� 
			stack.Push(s[i]);
		else if (s[i] == '(')//������ 
			signstack.Push(s[i]);
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') 
		{//�Ӽ��˳��˷������ 
			if (signstack.StackEmpty() == true)//����ջΪ�� 
				signstack.Push(s[i]);
			else if (s[i + 1] == ')' || signstack.GetTop() == '(')
			{
				signstack.Push(s[i]);
			}
			else if (signvalue(signstack.GetTop())<signvalue(s[i]))//����һ�����ȼ��� 
			{
				//stack.Push(s[i+1]);
				//stack.Push(s[i]);
				signstack.Push(s[i]);
			}
			else if (signvalue(signstack.GetTop()) >= signvalue(s[i]))//ǰ��һ�����ȼ����� 
			{
				stack.Push(signstack.GetTop());
				signstack.Pop();
				signstack.Push(s[i]);
			} 
		}
		else if (s[i] == ')')//������ 
		{

			while (signstack.GetTop() != '(')
			{
				stack.Push(signstack.GetTop());
				signstack.Pop();
			}
			signstack.Pop();
		}
		stack.PrintAll();
		signstack.PrintAll();
	}
	while (signstack.StackEmpty() == false)
	{
		stack.Push(signstack.GetTop());
		signstack.Pop();
	}
	cout<<"stack:";
	stack.PrintAll();
	cout<<"signstack";
	signstack.PrintAll();
	//���Ͻ����ʽ ��Ϊ������+������+���������ʽ ���沨�����ʽ

	int reslen = stack.GetCount();
	SqStack<int> res(reslen);//res��һ���洢�м���������˳��ջ
	for (int i = 0; i<reslen; i++)
	{
		if (stack.GetElem(i) >= '0'&&stack.GetElem(i) <= '9')
			res.Push(stack.GetElem(i) - '0');
		else
		{
			int cnt = res.GetCount();
			int num1 = res.GetTop();
			res.Pop();
			int num2 = res.GetTop();
			res.Pop();
			res.Push(cal(stack.GetElem(i), num2, num1));
		}
		cout << "res:";
		res.PrintAll();
	}
	cout << res.GetTop() << endl;
	return 0;
}
//5+6*(4+7)
//5+6*4-((3+5)*2+6)
//5+4^(2+3)
