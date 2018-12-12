#include<iostream>
#include<fstream>
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
};



//template<class E>
struct HuffmanTreeNode
{
	int weight;
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

	void select(int cur, int &r1, int &r2);
	//nodes[1-current]��ѡ��˫��Ϊ0����Ȩֵ��С���������r1,r2����λ�ã�
	void CreateHuffmanTree(character<E> leaves[], int n);//n���ַ�����

public:
	HuffmanTree(character<E> leaves[], int n);
	virtual ~HuffmanTree() {};
	void Encode(E ch);
	void Decode(string codestring);
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
struct Buffer
{
	char ch;//�ַ�
	unsigned int bits;//ʵ�ʵ�bits��
};

template<class E>
class Compressor
{
protected:
	HuffmanTree<E> *p;
	FILE *infp, *outfp;
	character<E> buffer;
	void Write(unsigned int bit);
	void WriteToOutfp();
public:
	Compressor();
	~Compressor();
	void Compress();
	void Decompress();
};


//һ�����ַ�������д��һ���أ����������еı�����Ϊ8ʱ �������е��ַ�д��Ŀ���ļ���
template<class E>
void Compressor<E>::Write(unsigned int bit)
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
void Compressor<E>::WriteToOutfp()
{
	unsigned int len = buffer.bits;
	if (len > 0)
		for (unsigned int i = 0; i < 8 - len; i++)
			Write(0);
}

template<class E>
void Compressor<E>::Compress()
{
	string infile, outfile; //����������ļ���
	cout << "�������ѹ�����ļ���:" << endl;
	cin >> infile;
	if ((infp = fopen(infile, "rb")) == NULL)
	{
		cout << "���ļ�ʧ��!" << endl;
		return;
	}
	fgetc(infp); //ȡ��Դ�ļ��ĵ�һ���ַ�
	if (feof(infp))
	{
		cout << "��Դ�ļ�!" << endl;
		return;
	}
	cout << "������ѹ����洢�ļ���";
	cin >> outfile;

	if ((outfp = fopen(outfile, "wb")) == NULL)
	{
		cout << "���ļ�ʧ�ܣ�" << endl;
		return;
	}

	cout << "��ʼѹ��...." << endl;

	const unsigned long n = 256;
	char ch[n];
	unsigned long w[n];
	unsigned long  size = 0;


	for��unsigned long i = 0; i < n; i++)
	{
		ch[i] = (char)i;
		w[i] = 0;
	}//��ʼ��

	rewind(infp);
	char cha = fgetc(infp);
	while (!feof(infp))
	{
		w[(unsigned char)cha]++;
		size++;
		cha = fgetc(infp);
	}

	if (p != NULL) delete[]p;
	p = new HuffmanTree<char>(ch, w, n, charIndex);//���ɹ�������
	rewind(outfp); //ʹĿ���ļ�ָ��ָ���ļ��Ŀ�ʼ��
	fwrite(&size, sizeof(unsigned long), 1, outfp);
	for (unsigned long i = 0; i < n; i++)
	{
		fwrite(&w[i], sizeof(unsigned long), 1, outfp);
	}
	buf.bits = 0;
	buf.ch = 0;
	rewind(infp);
	cha = fgetc(infp);
	while (!feof(infp))
	{
		string tmp = p->Encode(cha);
		for (unsigned long i = 0; i < tmp.length(); i++)
		{
			if (tmp[i] == '0')
				Write(0);
			else Write(1);
		}
		cha = fgetc(infp);
	}
	WriteToOutfp();

	fclose(infp);
	fclose(outfp);
}


void Compressor<E>::Decompress()
{
	string infile, outfile;
	cout << "�������ѹ�ļ�����";
	cin >> infile;
	if ((infp = fopen(infile, "rb")) == NULL)
	{
		cout << "�������ļ�����";
		return;
	}
	fgetc(infp);
	if (feof(infp))
	{
		cout << "ѹ���ļ�Ϊ�գ�";
		return;
	}

	cout << "�������ѹ����ļ�����";
	cin >> outfile;

	if ((outfp = fopen(outfile, "wb")) == NULL)
	{
		cout << "��Ŀ���ļ�ʧ�ܣ�";
	}
	cout << "���ڽ�ѹ...";

	const unsigned long n = 256;
	char ch[n];
	unsigned long w[n];
	unsigned long size = 0;
	char cha;

	rewind(infp);
	fread(&w[i], sizeof(unsigned long), 1, infp);
	for (unsigned long i = 0; i < n; i++)
	{
		ch[i] = (char)i;
		fread(&w[i], sizeof(unsigned long), 1, infp);
	}
	if (p != NULL)
		delete[] p;
	p = new HuffmanTree<char>(ch, w, n, CharIndex);

	unsigned long len = 0;
	cha = fgetc(infp);

	while (!feof(infp))
	{
		string tmp = "";
		unsigned char c = (unsigned char)cha;
		for (unsigned long i = 0; i < 8; i++)
		{
			if (c < 128) concat(tmp, "0");
			else concat(tmp, "1");
			c = c << 1;
		}
		LinkList<char> lkText = p->Decode(tmp);
		string strtemp(lkText);
		for (unsigned long i = 0; i < strtemp.length(); i++)
		{
			len++;
			fputc(strtemp[i], outfp);
			if (len == size) break;
		}
	}
	if (len == size) break;
	cha = fgetc(infp);
	fclose(infp);
	fclose(outfp);
	cout << "��ѹ������" << endl;
}



