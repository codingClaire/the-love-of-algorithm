#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;


template <class E>
struct Node//Node�ṹ
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
}//����ָ����Ϊ�յĽ��

template<class E>
Node<E>::Node(E item, Node<E>* link)
{
	data = item;
	next = link;
}

/*�����*/

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


template<class E>//����ĳλ�õ�ָ��
Node<E>* SimpleLinkedList<E>::GetElemPtr(int position) const //����ָ��Node��ָ������
{
	Node<E>* tmp = head;
	int curposition = 0;
	while (tmp != NULL&&curposition < position)//һֱ����ȥ������
	{
		tmp = tmp->next;
		curposition++;
	}
	if (tmp != NULL&&curposition == position)
		return tmp;
	else return NULL;
}

template <class E>//��ʼ��
void SimpleLinkedList<E>::Init()
{
	head = new Node<E>;//����ͷָ��
}

template <class E>//�޲ι��캯��
SimpleLinkedList<E>::SimpleLinkedList()
{
	Init();
}

template <class E>//��������
SimpleLinkedList<E>::~SimpleLinkedList()
{
	Clear();
	delete head;
}

template<class E>//������
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

template<class E>//�п�
bool SimpleLinkedList<E>::Empty() const
{
	if (head->next == NULL)
		return true;
	else return false;
}

template<class E>//�������
void SimpleLinkedList<E>::Clear()
{
	E tmp;
	while (Length() > 0)
		Delete(1, tmp);//���Ա�ǿ�ɾ����һ��Ԫ��
}

template<class E>//���������ÿһ��Ԫ��
void SimpleLinkedList<E>::Traverse(void(*Visit)(E &))
{
	Node<E>* tmp = head->next;
	for (; tmp != NULL; tmp = tmp->next)
		(*Visit)(tmp->data); //�����Ա��ÿ��Ԫ�ص��ú���(*Visit)
}

template <class E>//ȡ��position��Ԫ��
E SimpleLinkedList<E>::GetElem(int position) const
{
	Node<E>* tmp=head->next;
	for (int i = 0; i < position; i++)
	{
		tmp = tmp->next;
	}
	return tmp->data;
}

template<class E>//ȡ��position��Ԫ�� ����StatusCode
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
