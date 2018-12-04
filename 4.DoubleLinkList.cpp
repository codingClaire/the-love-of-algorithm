#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

template<class E> class DoubleLinkList;
template<class E> class DoubleNode
{
	friend class DoubleLinkList<E>
private:
	E data;
	DoubleNode<E> *leftlink, *rightlink;
	DoubleNode(E value,DoubleNode<E> *left,DoubleNode<E> *right):data(value),leftlink(left),rightlink(right){}
	DoubleNode(E value):data(value),leftlink(NULL),rightlink(NULL){}
};

template<class E> class DoubleLinkList
{
	DoubleLinkList(E val);
	~DoubleLinkList();
	int Length() const;
	int IsEmpty() { return first->rlink == first; }
	int Find(const E& target);
	E getData() const;
	int First();
	int Next();
	int Prior();
	void insert(const E &value);
	void Remove();
private:
	DoubleNode<E> *first, *current;
};

//搜索值为target
template<class E> 
int DoubleLinkList<E>::Find(const E &target)
{
	DoubleLinkList<E> *p = first->rightlink;
	while (p != first&&p->data != target)//栈不空且没有找到
	{
		p = p->rightlink;
	}
	if (p != first)
	{
		current = p;
		return 1;
	}
	return 0;
}

//插入结点
template<class E> 
void DoubleLinkList<E>::insert(const E &value)
{
	if (current == NULL)
		current = first->rightlink = new DoubleNode(value, first, first);
	else
	{
		current->rightlink = new DoubleNode(value, current, current->rightlink);
		current = current->rightlink;
	}

	current->rightlink->leftlink = current;

}

//删除结点
template<class E> 
void DoubleLinkList<E>::Remove()
{
	if (current != NULL)
	{
		current->rightlink->leftlink = current->leftlink;
		current->leftlink->rightlink = current->rightlink;
		current = current->rightlink;
		if (current == first)//删除的是最后一个结点 current 此时指向了first
		{
			if (IsEmpty())
				current = NULL; //链表没有元素了
			else
				current = current->rightlink;
			//双向循环链表 有头节点 此时要将current指向第一个元素（非头节点）
		}
	}
}

//构造函数 创建表头结点
template<class E> 
DoubleLinkList<E>::DoubleLinkList(E val)
{
	first = new DoubleNode<E>(val);
	first->rightlink = first->leftlink = first;
	current = NULL;
}

//求双向链表的长度
template<class E> 
int DoubleLinkList<E>::Length() const
{
	DoubleLinkList<E> *p = first->rightlink;
	int cnt = 0;
	while (p != first)
	{
		p = p->rightlink;
		cnt++;
	}
	return cnt;
}

//current指向第一个元素（第一个元素访问）
template<class E>
int DoubleLinkList<E>::First()
{
	if (!IsEmpty())
	{
		current = first->rightlink;
		return 1;
	}
	current = NULL;
	return 0;
} 

//访问下一个元素
template<class E>
int DoubleLinkList<E>::Next()
{
	if (current->rightlink != first)
	{
		current = current->rightlink;
		return 1;
	}
	current = NULL;
	return 1;
}

//访问上一个元素
template<class E>
int DoubleLinklist<E>::Prior()
{
	if (current->leftlink != first)
	{
		current = current->leftlink;
		return 1;
	}
	current = NULL;
	return 0;
}




class Editor
{
private:
	DoubleLinkList<string> textbuffer;
	int Linenum;
	DoubleLinkList<string> textundobuffer;
	int undoLinenum;
	ifstream inFile;
	ofstream outFile;
	void NextLine();
	void PreviousLine();
	void GotoLine();
	void InsertLine();
	void ReadFile();
	void WriteFile();
	void FindString();
public:
	Editor(char infName[], char outfName[]);
	void run();
};


