#include<iostream>
using namespace std;

template <class E>
struct Node
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
}

template<class E>
Node<E>::Node(E item, Node<E>* link)
{
	data = item;
	next = link;
}

template <class E>
class  LinkedList
{
protected:
	Node<E>* head;
	Node<E>* GetElemPtr(int position) const;
	void Init();
public:
	LinkedList();
	virtual ~LinkedList();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*Visit)(E &));
	StatusCode GetElem(int position, E &e) const;
	StatusCode SetElem(int position, const E &e);
	StatusCode Delete(int position, const E &e);
	StatusCode Insert(int position, const E &e);
	LinkedList(const LinkedList<E> &copy);
	LinkedList<E> &operator=(const LinkedList<E> &copy);
};