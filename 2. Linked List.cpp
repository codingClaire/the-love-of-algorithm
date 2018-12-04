#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;


template <class E>
struct Node//Node结构
{
	E data;
	Node<E>* next;
	
	Node();
	Node(E item, Node<E>* link=NULL);
};

template<class E>
Node<E>::Node()
{
	next = NULL;
}//构造指针域为空的结点

template<class E>
Node<E>::Node(E item, Node<E>* link)
{
	data = item;
	next = link;
}

/*结点类*/

template <class E>
class  SimpleLinkedList
{
protected:
	Node<E>* head;
	Node<E>* GetElemPtr(int position) const;
	void Init();
public:
	SimpleLinkedList();
	virtual ~SimpleLinkedList();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*Visit)(E &));
	E GetElem(int position) const;
	StatusCode GetElem(int position,E &e) const
	StatusCode SetElem(int position, const E &e);
	StatusCode Delete(int position, const E &e);
	StatusCode Insert(int position, const E &e);
	SimpleLinkedList(const SimpleLinkedList<E> &copy);
	SimpleLinkedList<E> &operator=(const SimpleLinkedList<E> &copy);
};


template<class E>//返回某位置的指针
Node<E>* SimpleLinkedList<E>::GetElemPtr(int position) const //返回指向Node的指针类型
{
	Node<E>* tmp = head;
	int curposition = 0;
	while (tmp != NULL&&curposition < position)//一直找下去的条件
	{
		tmp = tmp->next;
		curposition++;
	}
	if (tmp != NULL&&curposition == position)
		return tmp;
	else return NULL;
}

template <class E>//初始化
void SimpleLinkedList<E>::Init()
{
	head = new Node<E>;//构造头指针
}

template <class E>//无参构造函数
SimpleLinkedList<E>::SimpleLinkedList()
{
	Init();
}

template <class E>//析构函数
SimpleLinkedList<E>::~SimpleLinkedList()
{
	Clear();
	delete head;
}

template<class E>//链表长度
int SimpleLinkedList<E>::Length() const
{
	Node<E>* tmp = head->next;
	int cnt;
	for (cnt = 0; tmp != NULL; cnt++)
	{
		tmp = tmp->next;
	}
	return cnt;
}

template<class E>//判空
bool SimpleLinkedList<E>::Empty() const
{
	if (head->next == NULL)
		return true;
	else return false;
}

template<class E>//清空链表
void SimpleLinkedList<E>::Clear()
{
	E tmp;
	while (Length() > 0)
		Delete(1, tmp);//线性表非空删除第一个元素
}

template<class E>//遍历链表的每一个元素
void SimpleLinkedList<E>::Traverse(void(*Visit)(E &))
{
	Node<E>* tmp = head->next;
	for (; tmp != NULL; tmp = tmp->next)
		(*Visit)(tmp->data); //对线性表的每个元素调用函数(*Visit)
}

template <class E>//取第position个元素
E SimpleLinkedList<E>::GetElem(int position) const
{
	Node<E>* tmp=head->next;
	for (int i = 0; i < position; i++)
	{
		tmp = tmp->next;
	}
	return tmp->data;
}

template<class E>//取第position个元素 返回StatusCode
StatusCode SimpleLinkedList<E>::GetElem(int position, E &e) const
{
	if (position<1 || position>Length())
	{
		return Range_Error;
	}
	else
	{
		Node<E>* tmp;
		tmp = GetElemPtr(position);
		e = tmp->data;
		return Entry_Found;
	}
}
