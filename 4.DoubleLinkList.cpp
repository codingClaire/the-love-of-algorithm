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

//����ֵΪtarget
template<class E> 
int DoubleLinkList<E>::Find(const E &target)
{
	DoubleLinkList<E> *p = first->rightlink;
	while (p != first&&p->data != target)//ջ������û���ҵ�
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

//������
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

//ɾ�����
template<class E> 
void DoubleLinkList<E>::Remove()
{
	if (current != NULL)
	{
		current->rightlink->leftlink = current->leftlink;
		current->leftlink->rightlink = current->rightlink;
		current = current->rightlink;
		if (current == first)//ɾ���������һ����� current ��ʱָ����first
		{
			if (IsEmpty())
				current = NULL; //����û��Ԫ����
			else
				current = current->rightlink;
			//˫��ѭ������ ��ͷ�ڵ� ��ʱҪ��currentָ���һ��Ԫ�أ���ͷ�ڵ㣩
		}
	}
}

//���캯�� ������ͷ���
template<class E> 
DoubleLinkList<E>::DoubleLinkList(E val)
{
	first = new DoubleNode<E>(val);
	first->rightlink = first->leftlink = first;
	current = NULL;
}

//��˫������ĳ���
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

//currentָ���һ��Ԫ�أ���һ��Ԫ�ط��ʣ�
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

//������һ��Ԫ��
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

//������һ��Ԫ��
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


