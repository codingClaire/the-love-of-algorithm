#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<iomanip>
using namespace std;


/****************压缩***********************/
template<class E>
class HuffNode
{
public:
	HuffNode<E> *leftchild;//左孩子
	HuffNode<E> *rightchild;//右孩子
	int weight;//字符出现次数
	E ch;

	HuffNode();
	HuffNode(int w, E c);
	HuffNode(const HuffNode<E> &a);//拷贝构造
	HuffNode(const HuffNode<E> &a, const HuffNode<E> &b);
	bool operator <(HuffNode<E> &a);//运算符重载

};

template<class E>
static void Delete(HuffNode<E> *p)//删除结点
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
{//a、b两个结点生成一棵树，a、b作为新生成结点的左右子树 权值之和成为新节点的权值
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
class stack//使用排序栈
{
private:
	HuffNode<E> *s[256+5];
	int top; //栈顶
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
class HuffmanTree//HuffmanTree类
{
private:
	HuffNode<E> *root;//树的根节点
	int Weight[128];
	string HuffmanTable[128]; //第i个表示acsii码为i的字符对应的huffman编码
	void DFS(HuffNode<E> *p, string huffcode);
	int Bin(int i);//十进制转化为二进制
public:
	HuffmanTree();
	~HuffmanTree();
	void BuildTree(string infile);//建立哈夫曼树
	void GetHuffmanTable();//生成Huffman编码与字符的对应数组
	void HuffmanCode(const string &infile, const string &outfile);//文本转换为Huffman编码
};

template<class E>
void HuffmanTree<E>::DFS(HuffNode<E> *p, string huffcode)
{//深度优先
	if (p->ch != 0)
	{
		HuffmanTable[(int)p->ch] = huffcode;
		return;
	}
	if (p->leftchild != NULL)
		DFS(p->leftchild, huffcode + "0");
	if (p->rightchild != NULL)
		DFS(p->rightchild, huffcode + "1");
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
void HuffmanTree<E>::BuildTree(string infile)
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
		Weight[(int)c]++;//统计出现次数
	}
	in.close();

	stack<E> *s = new stack<E>();//考虑用栈按照权值进行排序
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
		if (s->Empty())//s非空
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
		GetHuffmanTable(); //每个字符对应的编码保存在HaffmanTable[128]
		fstream in, out;
		out.open(outfile.c_str(), ios::out);
		for (int i = 0; i < 128; i++)
			if (HuffmanTable[i].length() > 0)
			{
				out << setfill('0') << setw(7) << Bin(i) << setw(4) << Bin(HuffmanTable[i].size()) << HuffmanTable[i];
				//输出固定长度为7的ASCII码，后固定的4位纪录ASCII码对应的huffman编码的长度，最后是huffman编码。
				//解码时每次固定读入11位，前7位是ASCII码，后4位为需要读入的huffman码的码长，然后读入对应码长的huffman码
				//setfill和setw函数需要使用iomanip库
			}
		out << "00000000000";//最后输出11个0表示码表输出完毕,开始输出文档的huffman编码

		in.open(infile.c_str(), ios::in);
		string str;
		if (!in)
		{
			cout << "无法打开文件" << endl;
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


/****************解压************************/	

struct Node
{
    Node *leaf[2];
    char c;
    Node(){ c = '\0';leaf[0] = leaf[1] = NULL;}
};


class Trie
{
private:
    Node *root;//根节点
	void Delete(Node *p);
	void BuildTrie(fstream &in);//建立字典树
public:
	Trie();
	~Trie();
	void AddLeaf(const string &str, const char &c);//建立字典树的辅助函数
	void Decode(string infile, string outfile);//解压
	char GetASCII(const string &str);//返回前七位字符对应ascii码
	int GetLen(const string &str);//返回哈夫曼编码十进制长度
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
	string str, haffmancode; //haffmancode表示这个字符对应的二进制码
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
//前7位二进制转十进制，得到对应的ascii值
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
//后四位二进制转十进制，返回哈夫曼编码十进制长度
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
char HuffmanTree<E>::GetASCII(const string &str)//二进制转十进制
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
int HuffmanTree<E>::GetLen(const string &str)//二进制转十进制，返回哈夫曼编码十进制长度
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
string str, huffmancode; //huffmancode表示这个字符对应的二进制码
while (1)
{
str = "";
for (int i = 0; i < 11; i++)
{
str += in.get();
}//每次读取11位
if (str == "00000000000")
return;//结束读取
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
}//0加在左边
else
{
if (p->rightchild == NULL)
{
p->rightchild = new HuffNode<E>();
}
p = p->rightchild;
}//1加在右边
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
