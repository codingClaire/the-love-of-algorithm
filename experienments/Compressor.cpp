
#include<iostream>
#include<cstring>
#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
template<class E>
struct character
{
	int times; //���ֵĴ���
	E ch;//�ַ�
	string Huffmancode;//�ַ���Ӧ��huffman����
	int bits;//ʵ�ʵ�bits��
};

//template<class E>
struct HuffmanTreeNode
{
	int weight;
	//HuffmanTreeNode* parent; //˫�׽��ֻ��Ҫ֪��Ȩֵ����
	//HuffmanTreeNode* leftchild;
	//HuffmanTreeNode* rightchild;//˫�ס����ӡ��Һ���
	int parent, leftchild, rightchild;
	HuffmanTreeNode();
	HuffmanTreeNode(int w, int p, HuffmanTreeNode *l, HuffmanTreeNode *r);
};

template<class E>
class HuffmanTree
{
protected:
	HuffmanTreeNode *nodes;
	character<E> *leaf;
	int currentposition;
	int num;

	void select(int cur, int &r1, int &r2);//nodes[1-current]��ѡ��˫��Ϊ0����Ȩֵ��С���������r1,r2����λ�ã�
	void CreateHuffmanTree(character<E> leaves[], int n);//n���ַ�����

public:
	HuffmanTree(character<E> leaves[], int n);
	virtual ~HuffmanTree();
	string Encode(E ch);
	void Decode(string codestring);
	//HuffmanTree(const HuffmanTree<E>& copy);
	//HuffmanTree<E> &operator=(const HuffmanTree<E>& copy);
};


template<class E>
void HuffmanTree<E>::select(int cur, int &r1, int &r2)
{
	r1 = r2 = 0;//r1��r2�洢�˳��ִ�����С������Ҷ�ӵ�λ��
	for (int i = 1; i <= cur; i++)
	{
		if (nodes[i].parent != 0)
			continue;
		if (r1 == 0) r1 = i;
		else if (r2 == 0) r2 = i;
		else if (nodes[i].weight < nodes[r1].weight)
			r1 = i;
		else if (nodes[i].weight < nodes[r2].weight)
			r2 = i;
	}
}

template<class E>
void HuffmanTree<E>::CreateHuffmanTree(character<E> leaves[], int n)//�����ַ��������Ϣ
{
	num = n;
	int m = 2 * n - 1;
	nodes = new HuffmanTreeNode[m + 1];
	leaf = new character<E>[n + 1];
	for (int i = 1; i <= n; i++)
	{
		nodes[i].weight = leaves[i - 1]->times;
		leaf[i] = leaves[i - 1]->ch;
	} //��ʱ nodes[0]��leaf[0]��û��ʹ��
	for (int i = n + 1; i <= m; i++)
	{
		int r1, r2;
		select(i, r1, r2);
		nodes[r1].parent = nodes[r2].parent = i;
		nodes[i].leftchild = r1;
		nodes[i].rightchild = r2;
		nodes[i].weight = nodes[r1].weight + nodes[r2].weight;
	}
	string charcode; 
	for (int i = 1; i <= n; i++)
	{
		for (unsigned int child = i, parent = nodes[child].parent != 0; parent != 0; child = parent, parent = nodes[child].parent)
		{
			if (nodes[parent].leftchild == child)
				charcode.insert(1, '0');
			else charcode.insert(1, '1');
		}
		leaf[i].Huffmancode = charcode;
	}
	currentposition = m;
}

template<class E>
HuffmanTree<E>::HuffmanTree(character<E> leaves[], int n)
{
	CreateHuffmanTree(leaves, n);
}

template<class E>
string HuffmanTree<E>::Encode(E chara)
{
	for (int i = 0; i < num; i++)
	{
		if (leaf[i].ch == chara)
			return leaf[i].Huffmancode;
	
	}
	cout << "Error:The character is illegal!" << endl;
}

template<class E>
void HuffmanTree<E>::Decode(string codestring)
{
	for (int i = 0; i < num; i++)
	{
		if (leaf[i].Huffmancode == codestring)
			return leaf[i].ch;
	}
}

/****************************************************************/
template<class E>
class Compress
{
protected:
	HuffmanTree<E> *p;
	FILE *infp, *outfp;
	character<E> buffer;
	void Write(unsigned int bit);
	void WriteToOutfp();
public:
	Compress();
	~Compress();
	void Compressing();
};


//һ�����ַ�������д��һ���أ����������еı�����Ϊ8ʱ �������е��ַ�д��Ŀ���ļ���
template<class E>
void Compress<E>::Write(unsigned int bit)
{
	buffer.bits++;
	buffer.ch = (buffer.ch << 1) | bit;
	if (buffer.bits == 8)
	{
		fputc(buffer.ch, outfp);
		buffer.bits = 0;
		buffer.ch = 0;
	}
}

//���������WritetoOutfp �ڹ������������ʱ��ǿ�н�����д��Ŀ���ļ���
template<class E>
void Compress<E>::WriteToOutfp()
{
	unsigned int len = buffer.bits;
	if (len > 0)
		for (unsigned int i = 0; i < 8 - len; i++)
			Write(0);
}

template<class E>
void Compress<E>::Compressing()
{
	char infile[256], outfile[256];
	cout << "input the name of the original file you want to be compressed:" << endl;
	cin >> infile;
	if ((infp = fopen(infile, "rb")) == NULL)
	{
		cout << "Fail to open the original file!" << endl;
		return;
	}
	fgetc(infp);
	if (feof(infp))
	{
		cout << "Empty original file!" << endl;
		return;
	}
}
template<class E>
class Decompress
{
protected:
	HuffmanTree<E> *p;
	FILE *infp, *outfp;
	character<E> buffer;

	void Read(unsigned int bit);
	void ReadFromOutfp();
public:
	Decompress();
	~Decompress();
};


int main()
{
	character<char> string1[10];
	for (int i = 0; i < 10; i++)
	{
		string1[i].ch = 'a' + i;
		string1[i].times = 10 - i;
	}
	int n = 10;
	HuffmanTree<char> tree1(character<char> string1[10], int n);


	return 0;
}

