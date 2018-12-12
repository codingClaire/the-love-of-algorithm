#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<iomanip>
using namespace std;

template<class E>
class HuffNode
{
public:
	HuffNode<E> *leftchild;
	HuffNode<E> *rightchild;
	int weight;
	E ch;

	HuffNode();
	HuffNode(int w, int c);
	HuffNode(const HuffNode<E> &a);
	HuffNode(const HuffNode<E> &a, const HuffNode<E> &b);
	bool operator <(HuffNode a, HuffNode b);
	void Delete(HuffNode *p);

};

template<class E>
HuffNode<E>::HuffNode()
{
	leftchild = NULL;
	rightchild = NULL;
	weight = 0;
	ch = 0;
}

template<class E>
HuffNode<E>::HuffNode(int w, char c)
{
	leftchild = NULL;
	rightchild = NULL;
	weight = w;
	ch = c;
}

template<class E>
HuffNode<E>::HuffNode(const HuffNode<E> &a)
{
	leftchild = a.leftchild;
	rightchild = a.rightchild;
	weight = a.weight;
	ch = a.ch;
}

template<class E>
HuffNode<E>::HuffNode(const HuffNode<E> &a, const HuffNode<E> &b)
{
	r = new HuffNode(a.weight, a.ch);
	r->leftchild = a.leftchild;
	r->rightchild = a.rightchild;

	l = new HuffNode(b.weight, b.ch);
	l->leftchild = b.leftchild;
	l->rightchild = b.rightchild;
	weight = a.weight + b.weight;
}

template<class E>
bool HuffNode<E>::operator <(HuffNode &a)
{
	return a.weight < weight;
}

template<class E>
void HuffNode<E>::Delete(HuffNode *p)
{
	if (p->leftchild != NULL)
	{
		Delete(p->leftchild);
		delete(p->leftchild);
	}
	if (p->rightchild != NULL)
	{
		Delete(p->rightchild);
		delete(p->rightchild);
	}
}


int maxn = 256;
template<class E>
class stack
{
private:
	HuffNode<E> *s[maxn];
	int top; //栈顶
public:
	stack() { top = -1; }
	void push(HuffNode &item);
	HuffNode* pop();
	bool Empty();
};

template<class E>
void stack<E>::push(HuffNode &item)
{
	HuffNode *m[128];
	int num;
	while (top != -1 && s[top]->weight < item.weight)
	{
		m[i] = pop();
		num++;
	}
	top++;
	s[top] = new HuffNode(item);
	while (num--)
	{
		top++;
		s[top] = new HuffNode(m[i]);
	}
	return;
}

template<class E>
HuffNode* stack<E>::pop()
{
	HuffNode *tmp = new Node(s[top]);
	s[top] = NULL;
	top--;
	return tmp;
}

template<class E>
bool stack<E>::Empty()
{
	return top == -1;
}

template<class E>
class HuffmanTree
{
private:
	HuffNode<E> *root;
	int Weight[128];
	string HuffmanTable[128];
	//string infile, outfile;

	void DFS(HuffNode *p, string huffcode);
	int Bin(int i);
public:
	HuffmanTree();
	~HuffmanTree();
	void BuildTree();
	void GetHuffmanTable();
	void HuffmanCode();
};










template<class E>
void HuffmanTree<E>::DFS(Node *p, string huffcode)
{
	if (p->ch != 0)
	{
		HuffmanTable[(int)p->ch] = route;
		return;
	}
	if (p->leftchild != NULL)
		DFS(p->leftchild, route + "0");
	if (p->rightchild != NULL)
		DFS(p->rightchild, route + "1");
	//递归：求出HuffmanTable字符对应的huffman编码
}

template<class E>
int HuffmanTree<E>::Bin(int i)
{
	int res = 0;
	int pow = 1;
	while (i)
	{
		res += pow*(i & 1);
		i = i >> 1;//右移一位
		pow = pow * 10;
	}
	return res;
}

template<class E>
HuffmanTree<E>::HuffmanTree()
{
	root = NULL;
	memset(Weight, 0, sizeof(Weight));
}

template<class E>
HuffmanTree<E>::~HuffmanTree()
{
	if (root != 0) 
		Delete(root);
}

template<class E>
void HuffmanTree<E>::BuildTree()
{
	fstream in;
	in.open(infile.c_str(), ios::in);
	if (!in)
	{
		cout << "无法打开文件！" << endl;
		return;
	}

	while (1)
	{
		char c;
		in.get(c);
		if (in.eof())
			break;
		Weight[(int)c]++;
	}
	in.close();

	stack<E> *s = new stack;
	for (int i = 0; i < 128; i++)
	{
		if (Weight[i] != 0)
		{
			HuffNode<E> *nd = new HuffNode(Weight[i], i);
			s->push(*nd);
		}
	}
	while (1)
	{
		HuffNode<E> *nd1 = new HuffNode();
		HuffNode<E> *nd2 = new HuffNode();
		nd1 = s->pop();
		if (s->Empty())//s非空
		{
			s->push(*nd1);
			break;
		}
		nd2 = s->pop();
		HuffNode *newtree = new HuffNode(*nd1, *nd2);
		s->push(*newtree);
	}
	root = s->pop();
	delete s;
}

template<class E>
void  HuffmanTree<E>::GetHuffmanTable()
{

}