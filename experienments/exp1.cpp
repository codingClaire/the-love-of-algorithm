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
	int count;//栈中存储元素个数
	int maxSize;//栈的最大存储量
	E *elems;//elems数组
	E *now;//指向当前元素的指针 
	bool full() const;//判满
	void Init(int size);//初始化
public:
	SqStack(int size = DEFAULT_SIZE);
	virtual ~SqStack();
	int StackLength();//栈的长度
	bool StackEmpty();//判断栈是否空
	E GetTop();//取栈顶元素
	E GetElem(int i);//返回第i个栈内的元素
	void ClearStack();//清空栈
	bool Push(E x);//元素进栈
	bool Pop();//元素出栈
	int GetCount() { return count; }//栈内元素个数
	int GetMaxSize() { return maxSize; }//栈的最大存储量

	void PrintAll();//打印栈内元素

};


template<class E>
bool SqStack<E>::full() const
{
	return count == maxSize;
}

template<class E>
void SqStack<E>::Init(int size)
{//初始化栈 最大元素个数为size
	maxSize = size;
	count = 0;
	if (elems != NULL)
		delete[]elems;//释放
	elems = new E[maxSize];
	now = elems;
}

template<class E>
SqStack<E>::SqStack(int size)
{
	cout << "一个新栈正在生成.栈大小为:" << size << endl;
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
		cout << "pop element：" << *now << endl;
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
}//函数返回运算符对应值，运算优先级排序 

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
	//字符类型栈,stack存储的是数字结果，signstack存储符号 
	for (int i = 0; i<len; i++)
	{
		if (s[i] >= '0'&&s[i] <= '9')//数字 
			stack.Push(s[i]);
		else if (s[i] == '(')//左括号 
			signstack.Push(s[i]);
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') 
		{//加减乘除乘方运算符 
			if (signstack.StackEmpty() == true)//符号栈为空 
				signstack.Push(s[i]);
			else if (s[i + 1] == ')' || signstack.GetTop() == '(')
			{
				signstack.Push(s[i]);
			}
			else if (signvalue(signstack.GetTop())<signvalue(s[i]))//后面一个优先级高 
			{
				//stack.Push(s[i+1]);
				//stack.Push(s[i]);
				signstack.Push(s[i]);
			}
			else if (signvalue(signstack.GetTop()) >= signvalue(s[i]))//前面一个优先级更高 
			{
				stack.Push(signstack.GetTop());
				signstack.Pop();
				signstack.Push(s[i]);
			} 
		}
		else if (s[i] == ')')//右括号 
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
	//以上将表达式 化为操作数+操作数+运算符的形式 即逆波兰表达式

	int reslen = stack.GetCount();
	SqStack<int> res(reslen);//res是一个存储中间运算结果的顺序栈
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
