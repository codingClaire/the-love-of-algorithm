#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<iomanip>
using namespace std;


/****************ѹ��***********************/
template<class E>
class HuffNode
{
public:
	HuffNode<E> *leftchild;//����
	HuffNode<E> *rightchild;//�Һ���
	int weight;//�ַ����ִ���
	E ch;

	HuffNode();
	HuffNode(int w, E c);
	HuffNode(const HuffNode<E> &a);//��������
	HuffNode(const HuffNode<E> &a, const HuffNode<E> &b);
	bool operator <(HuffNode<E> &a);//���������

};

template<class E>
static void Delete(HuffNode<E> *p)//ɾ�����
{
	if (p->leftchild != NULL)
    {
        Delete(p->leftchild);
        delete (p->leftchild);
    }
    if (p->rightchild != NULL)
    {
        Delete(p->rightchild);
        delete (p->rightchild);
    }

}

template<class E>
HuffNode<E>::HuffNode()
{
	leftchild = NULL;
	rightchild = NULL;
	weight = 0;
	ch = 0;
}

template<class E>
HuffNode<E>::HuffNode(int w, E c)
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
{//a��b�����������һ������a��b��Ϊ�����ɽ����������� Ȩֵ֮�ͳ�Ϊ�½ڵ��Ȩֵ
 		rightchild = new HuffNode<E>(a.weight, a.ch); 
        rightchild->leftchild = a.leftchild;
        rightchild->rightchild = a.rightchild;
        leftchild = new HuffNode<E>(b.weight, b.ch);  
        leftchild->leftchild = b.leftchild;
        leftchild->rightchild = b.rightchild;
        weight = a.weight + b.weight;
        ch = 0;

}

template<class E>
bool HuffNode<E>::operator <(HuffNode &a)
{
	return a.weight < weight;
}

int maxn = 256;
template<class E>
class stack//ʹ������ջ
{
private:
	HuffNode<E> *s[256+5];
	int top; //ջ��
public:
	stack() { top = -1; }
	void push(HuffNode<E> &item);
	HuffNode<E>* pop();
	bool Empty();
};

template<class E>
void stack<E>::push(HuffNode<E> &item)
{
	HuffNode<E> *m[128];
	int num=0;
	while (top != -1 && s[top]->weight < item.weight)
	{
		m[num] = pop();
		num++;
	}
	top++;
	//s[top] = HuffNode<E>(item);
	s[top] = new HuffNode<E>();
    s[top]->ch = item.ch;
    s[top]->leftchild = item.leftchild;
    s[top]->rightchild = item.rightchild;
    s[top]->weight = item.weight;

	while (num--)
	{
		top++;
	//	s[top] = HuffNode<E>(*m[num]);
		s[top] = new HuffNode<E>();
        s[top]->ch = m[num]->ch;
        s[top]->leftchild = m[num]->leftchild;
        s[top]->rightchild = m[num]->rightchild;
        s[top]->weight = m[num]->weight;

	}
	return;
}

template<class E>
HuffNode<E>* stack<E>::pop()
{
	HuffNode<E> *tmp = new HuffNode<E>(*s[top]);
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
class HuffmanTree//HuffmanTree��
{
private:
	HuffNode<E> *root;//���ĸ��ڵ�
	int Weight[128];
	string HuffmanTable[128]; //��i����ʾacsii��Ϊi���ַ���Ӧ��huffman����
	void DFS(HuffNode<E> *p, string huffcode);
	int Bin(int i);//ʮ����ת��Ϊ������
public:
	HuffmanTree();
	~HuffmanTree();
	void BuildTree(string infile);//������������
	void GetHuffmanTable();//����Huffman�������ַ��Ķ�Ӧ����
	void HuffmanCode(const string &infile, const string &outfile);//�ı�ת��ΪHuffman����
};

template<class E>
void HuffmanTree<E>::DFS(HuffNode<E> *p, string huffcode)
{//�������
	if (p->ch != 0)
	{
		HuffmanTable[(int)p->ch] = huffcode;
		return;
	}
	if (p->leftchild != NULL)
		DFS(p->leftchild, huffcode + "0");
	if (p->rightchild != NULL)
		DFS(p->rightchild, huffcode + "1");
	//�ݹ飺���HuffmanTable�ַ���Ӧ��huffman����
}

template<class E>
int HuffmanTree<E>::Bin(int i)
{
	int res = 0;
	int pow = 1;
	while (i)
	{
		res += pow*(i & 1);
		i = i >> 1;//����һλ
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
void HuffmanTree<E>::BuildTree(string infile)
{ 
	fstream in;
	in.open(infile.c_str(), ios::in);
	if (!in)
	{
		cout << "�޷����ļ���" << endl;
		return;
	}

	while (1)
	{
		char c;
		in.get(c);
		if (in.eof())
			break;
		Weight[(int)c]++;//ͳ�Ƴ��ִ���
	}
	in.close();

	stack<E> *s = new stack<E>();//������ջ����Ȩֵ��������
	for (int i = 0; i < 128; i++)
	{
		if (Weight[i] != 0)
		{
			HuffNode<E> *nd = new HuffNode<E>(Weight[i], i);
			s->push(*nd);
		}
	}
	while (1)
	{
		HuffNode<E> *nd1 = new HuffNode<E>();
		HuffNode<E> *nd2 = new HuffNode<E>();
		nd1 = s->pop();
		if (s->Empty())//s�ǿ�
		{
			s->push(*nd1);
			break;
		}
		nd2 = s->pop();
		HuffNode<E> *newtree = new HuffNode<E>(*nd1, *nd2);
		s->push(*newtree);
	}
	root = s->pop();
	delete s;
}

template<class E>
void HuffmanTree<E>::HuffmanCode(const string &infile, const string &outfile)
{
		if (root == NULL)
			return;
		GetHuffmanTable(); //ÿ���ַ���Ӧ�ı��뱣����HaffmanTable[128]
		fstream in, out;
		out.open(outfile.c_str(), ios::out);
		for (int i = 0; i < 128; i++)
			if (HuffmanTable[i].length() > 0)
			{
				out << setfill('0') << setw(7) << Bin(i) << setw(4) << Bin(HuffmanTable[i].size()) << HuffmanTable[i];
				//����̶�����Ϊ7��ASCII�룬��̶���4λ��¼ASCII���Ӧ��huffman����ĳ��ȣ������huffman���롣
				//����ʱÿ�ι̶�����11λ��ǰ7λ��ASCII�룬��4λΪ��Ҫ�����huffman����볤��Ȼ������Ӧ�볤��huffman��
				//setfill��setw������Ҫʹ��iomanip��
			}
		out << "00000000000";//������11��0��ʾ���������,��ʼ����ĵ���huffman����

		in.open(infile.c_str(), ios::in);
		string str;
		if (!in)
		{
			cout << "�޷����ļ�" << endl;
			return;
		}
		while (1)
		{
			char c;
			in.get(c);
			if (in.eof())
				break;
			out << HuffmanTable[(int)c];
		}
		in.close();
		out.close();
}	

template<class E>
void  HuffmanTree<E>::GetHuffmanTable()
{
	if (root != NULL)
		DFS(root, "");
}


/****************��ѹ************************/	

struct Node
{
    Node *leaf[2];
    char c;
    Node(){ c = '\0';leaf[0] = leaf[1] = NULL;}
};


class Trie
{
private:
    Node *root;//���ڵ�
	void Delete(Node *p);
	void BuildTrie(fstream &in);//�����ֵ���
public:
	Trie();
	~Trie();
	void AddLeaf(const string &str, const char &c);//�����ֵ����ĸ�������
	void Decode(string infile, string outfile);//��ѹ
	char GetASCII(const string &str);//����ǰ��λ�ַ���Ӧascii��
	int GetLen(const string &str);//���ع���������ʮ���Ƴ���
};

void Trie::Delete(Node *p)
{
	if (p->leaf[0] != NULL)
		Delete(p->leaf[0]);
	if (p->leaf[1] != NULL)
		Delete(p->leaf[1]);
	delete p;
}

void Trie::BuildTrie(fstream &in)
{
	string str, haffmancode; //haffmancode��ʾ����ַ���Ӧ�Ķ�������
	while (1)
	{
		str = "";
		for (int i = 0; i < 11; i++)
		{
			str += in.get();
		}
		if (str == "00000000000")
			return;
		int len = GetLen(str);
		haffmancode = "";
		for (int i = 0; i < len; i++)
		{
			haffmancode += in.get();
		}
		AddLeaf(haffmancode, GetASCII(str));
	}
}

Trie::Trie()
{
	root = new Node();
}

Trie::~Trie()
{
	Delete(root);
}

void Trie::AddLeaf(const string &str, const char &c)
{
	Node *p = root;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '0')
		{
			if (p->leaf[0] == NULL)
			{
				p->leaf[0] = new Node();
			}
			p = p->leaf[0];
		}
		else
		{
			if (p->leaf[1] == NULL)
			{
				p->leaf[1] = new Node();
			}
			p = p->leaf[1];
		}
	}
	p->c = c;
}

void Trie::Decode(string infile, string outfile)
{
	fstream in, out;
	in.open(infile.c_str(), ios::in);
	out.open(outfile.c_str(), ios::out);
	BuildTrie(in);
	Node *p = root;
	while (1)
	{
		char ci;
		in.get(ci);
		if (in.eof())
			return;
		if (ci == '0')
			p = p->leaf[0];
		else
			p = p->leaf[1];
		if (p->leaf[0] == NULL && p->leaf[1] == NULL)
		{
			out << p->c;
			p = root;
		}
	}
	in.close();
	out.close();
}

char Trie::GetASCII(const string &str)
//ǰ7λ������תʮ���ƣ��õ���Ӧ��asciiֵ
{
	int res = 0, pow = 1;
	for (int i = 6; i >= 0; i--)
	{
		res += (str[i] - '0') * pow;
		pow <<= 1;
	}
	return (char)res;
}

int Trie::GetLen(const string &str)
//����λ������תʮ���ƣ����ع���������ʮ���Ƴ���
{
	int res = 0, pow = 1;
	for (int i = 10; i >= 7; i--)
	{
		res += (str[i] - '0') * pow;
		pow <<= 1;
	}
	return res;
}

int main()
{
	string infile = "input.txt", outfile = "output.txt", decodefile = "decode.txt";
	HuffmanTree<char> A;
	A.BuildTree(infile);
	A.HuffmanCode(infile, outfile);
	Trie B;
	B.Decode(outfile, decodefile);

	return 0;
}


















/*

char GetASCII(const string &str);
int GetLen(const string &str);
void AddLeaf(const string &str, const E &c);
void HuffmanDecode(const string &infile, const string &outfile);
void BuildTrie(fstream &in);



template<class E>
char HuffmanTree<E>::GetASCII(const string &str)//������תʮ����
{
int res = 0, pow = 1;
for (int i = 6; i >= 0; i--)
{
res += (str[i] - '0') * pow;
pow <<= 1;
}
return (char)res;
}

template<class E>
int HuffmanTree<E>::GetLen(const string &str)//������תʮ���ƣ����ع���������ʮ���Ƴ���
{
int res = 0, pow = 1;
for (int i = 10; i >= 7; i--)
{
res += (str[i] - '0') * pow;
pow <<= 1;
}
return res;
}

template<class E>
void HuffmanTree<E>::BuildTrie(fstream &in)
{
string str, huffmancode; //huffmancode��ʾ����ַ���Ӧ�Ķ�������
while (1)
{
str = "";
for (int i = 0; i < 11; i++)
{
str += in.get();
}//ÿ�ζ�ȡ11λ
if (str == "00000000000")
return;//������ȡ
int len = GetLen(str);
huffmancode = "";
for (int i = 0; i < len; i++)
{
huffmancode += in.get();
}
AddLeaf(huffmancode, GetASCII(str));
cout<<huffmancode<<" "<<(char)GetASCII(str)<<endl;
}
}

template<class E>
void HuffmanTree<E>::AddLeaf(const string &str, const E &c)
{
HuffNode<E> *p = root;
for (int i = 0; i < str.size(); i++)
{
if (str[i] == '0')
{
if (p->leftchild== NULL)
p->leftchild= new HuffNode<E>();
p = p->rightchild;
}//0�������
else
{
if (p->rightchild == NULL)
{
p->rightchild = new HuffNode<E>();
}
p = p->rightchild;
}//1�����ұ�
}
p->ch = c;
}

template<class E>
void HuffmanTree<E>::HuffmanDecode(const string &infile, const string &outfile)
{
fstream in, out;
in.open(infile.c_str(), ios::in);
out.open(outfile.c_str(), ios::out);
BuildTrie(in);
//cout<<"I AM DECODING"<<endl;
HuffNode<E> *p=root;

while (1)
{
char ci;
in.get(ci);
if (in.eof())
return;
if (ci == '0')
p = p->leftchild;
else
p = p->rightchild;
if (p->leftchild == NULL && p->rightchild == NULL)
{
cout<<p->ch;
out << p->ch;
p = root;
}
}
in.close();
out.close();
}


*/
