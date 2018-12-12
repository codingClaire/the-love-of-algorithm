#include<iostream>
#include<fstream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
template<class E> class DoubleLinkList;
template<class E> class DoubleNode
{
	friend class DoubleLinkList<E>;
	//����Ϊ��Ԫ��������DoubleLinkList�еĳ�Ա�������Ե���DoubleNode�е�˽�г�Ա
private:
	E data; //Ԫ��ֵ
	DoubleNode<E> *leftlink, *rightlink; //��ָ�룬��ָ��
	DoubleNode(E value, DoubleNode<E> *left, DoubleNode<E> *right) :data(value), leftlink(left), rightlink(right) {}
	DoubleNode(E value) :data(value), leftlink(NULL), rightlink(NULL) {}
	DoubleNode(){}
	//�������캯��
};

template<class E> class DoubleLinkList
{
public:
	DoubleLinkList(E val); //���캯��
	DoubleLinkList();
	virtual ~DoubleLinkList() {}; //��������
	int Length(); //��˫������ĳ���
	bool Empty() { return first->rightlink == first; } //�ж��Ƿ�Ϊ��
	bool Find(const E& target);//����Ԫ�صĲ���

	int CurrentPosition() const { return curPosition; } //���ص�ǰλ��
	bool GetElem(int position, E& get); //����λ��Ϊposition��Ԫ��
	bool SetElem(int position, const E &e); //�趨λ��Ϊposition��Ԫ��ֵ
	bool Insert(int position, const E &value); //����Ԫ��
	bool Delete(int position, E &e); //ɾ��Ԫ��
	bool First(); //ȡ��һ��Ԫ��
	bool Next(); // ȡ��һ��Ԫ��
	bool Prior(); //ȡ��һ��Ԫ��
	void Init();//��ʼ��˫������
protected:
	DoubleNode<E> *first, *current; //firstͷ�ڵ�ָ�� currentָ��ǰ����ָ��
	int curPosition;//��ǰ����λ��
	int count;//Ԫ�ص��ܸ���
			  /*��������*/
	DoubleNode<E> *GetElemPtr(int position);//����ָ���position������ָ��
	
};

template<class E>
DoubleNode<E>* DoubleLinkList<E>::GetElemPtr(int position)
{
	if (curPosition < position)
	{	// ��ǰλ����������λ��֮ǰ,������
		while (curPosition < position)
		{
			current = current->rightlink;
			curPosition++;
		}
	}
	else if (curPosition>position)
	{	// ��ǰλ����������λ��֮��,��ǰ����
		while (curPosition > position)
		{
			current = current->leftlink;
			curPosition--;
		}
	}
	return current;
}

template<class E>
void DoubleLinkList<E>::Init()
{
	first = new DoubleNode<E>; //����ͷָ��
	first->leftlink = first;
	first->rightlink = first;//˫��ѭ�������ͷָ��ǰ���ͺ�̾�Ϊͷ�ڵ㱾��
	curPosition = 0;//��ǰλ������Ϊ0
	current = first;//���ҵ�ǰָ��Ҳָ��ͷ�ڵ�
	count = 0;//Ԫ���ܸ���Ϊ0
}

template<class E>
bool DoubleLinkList<E>::Find(const E &target)
{
	DoubleLinkList<E> *p = first->rightlink;
	while (p != first&&p->data != target)//������û���ҵ�
	{
		p = p->rightlink;
	}
	if (p != first)
	{
		current = p;
		return true; //�ɹ��ҵ� �����޸�currentָ�� ʹ��ָ��ҪѰ�ҵ�ֵ
	}
	return false;//����ʧ��
}

template<class E>
bool DoubleLinkList<E>::Insert(int position, const E &value)
{
	
	if (position<1 || position>Length() + 1)
		return false;
	else
	{	// position�Ϸ�
		DoubleNode<E> *tmpPtr, *nextPtr, *newPtr;
		tmpPtr = GetElemPtr(position - 1);	// ȡ��ָ���position-1������ָ��
		nextPtr = tmpPtr->rightlink;				// nextPtrָ���position�����	
		newPtr = new DoubleNode<E>(value, tmpPtr, nextPtr);// �����½��
		tmpPtr->rightlink = newPtr;				// �޸����ҵ�ָ��
		nextPtr->leftlink = newPtr;				// �޸������ָ��
		curPosition = position;				// ���õ�ǰλ�õ����
		current = newPtr;					// ����ָ��ǰλ�õ�ָ��
		count++;							// ����ɹ���Ԫ�ظ�����1 
		return true;
	} 
}

template<class E>
bool DoubleLinkList<E>::Delete(int position,E &e)
{//ɾ�����
	if (position<1 || position>Length())
		return false;//position�ķ�Χ����
	else //if (current != NULL)
	{
		current = GetElemPtr(position - 1);
		current = current->rightlink;
		current->rightlink->leftlink = current->leftlink;
		current->leftlink->rightlink = current->rightlink;
		//current = current->rightlink;
		e = current->data;
		if (position == Length())//ɾ���������һ����� current ��ʱָ����first
		{
			curPosition = 0;
			current = first;
		}
		else
		{
			curPosition = position;
			current = current->rightlink;
			//˫��ѭ������ ��ͷ�ڵ� ��ʱҪ��currentָ���һ��Ԫ�أ���ͷ�ڵ�)
		}
		count--;
		return true;
	}
}

template<class E>
DoubleLinkList<E>::DoubleLinkList()
{
	Init();
}

template<class E>
int DoubleLinkList<E>::Length()
{//��˫������ĳ���
	DoubleNode<E> *p = first->rightlink;
	int cnt = 0;
	while (p!= first)
	{
		p = p->rightlink;
		cnt++;
	}
	return cnt;
}

template<class E>
bool DoubleLinkList<E>::First()
{//currentָ���һ��Ԫ�أ���һ��Ԫ�ط��ʣ�
	if (!Empty())
	{
		current = first->rightlink;
		return true;
	}
	current = NULL;
	return false;
}

template<class E>
bool DoubleLinkList<E>::Next()
{//������һ��Ԫ��
	if (current->rightlink != first)
	{
		current = current->rightlink;
		return true;
	}
	current = NULL;
	return true;
}

template<class E>
bool DoubleLinkList<E>::Prior()
{//������һ��Ԫ��
	if (current->leftlink != first)
	{
		current = current->leftlink;
		return true;
	}
	current = NULL;
	return false;
}

template <class E>
bool DoubleLinkList<E>::GetElem(int position, E &e)
// ��������������Ա���ڵ�position��Ԫ��ʱ����e������ֵ
{
	if (position < 1 || position > Length())
		return false;
	else
	{	// position�Ϸ�
		DoubleNode<E> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��	
		e = tmpPtr->data;				// ��e���ص�position��Ԫ�ص�ֵ
		return true;
	}
}

template <class E>
bool DoubleLinkList<E>::SetElem(int position, const E &e)
// �����Ա�ĵ�position��λ�õ�Ԫ�ظ�ֵΪe,
//	position��ȡֵ��ΧΪ1��position��Length()
{
	if (position < 1 || position > Length())
		return true;
	else
	{	// position�Ϸ�
		DoubleNode<E> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��
		tmpPtr->data = e;				// ���õ�position��Ԫ�ص�ֵ
		return true;
	}
}
/**************************************************/
class Editor
{
private:
	DoubleLinkList<string> textbuffer; //�ı����棨˫��ѭ������
	int curLineNo;//��ǰ�к�
	DoubleLinkList<string> textundobuffer; //�ָ��ı����棨˫��ѭ������
	int curUndoLineNo;//�ָ��ĵ�ǰ�к�
	ifstream inFile; //�����ļ�
	ofstream outFile; //����ļ�
	string infName, outfName;
	bool NextLine(); //ת����һ��
	bool PreviousLine();
	bool GotoLine();
	bool InsertLine();
	void ChangeLine();
	void FindString();
	void ReadFile();
	void WriteFile();
	
public:
	Editor(string inf, string outf);
	void run();
};

Editor::Editor(string inf,string outf)
{
	//inFile.open(infName.c_str(), ios::in);
	//outFile.open(outfName.c_str(), ios::out);
	infName = inf;
	outfName = outf;
	curLineNo=0;
	curUndoLineNo=0;
}

bool Editor::NextLine()
{
	if (curLineNo == textbuffer.Length())
		return false;
	else
	{
		string nextline;
		curLineNo++; 
		textbuffer.GetElem(curLineNo, nextline);
		cout << "��һ����:" << nextline << endl;
		return true;
	}
}

bool Editor::PreviousLine()
{
	if (curLineNo==1)
		return false;
	else
	{
		string previousline;
		curLineNo--;
		textbuffer.GetElem(curLineNo, previousline);
		cout << "��һ���ǣ�" << previousline << endl;
		return true;
	}
}

bool Editor::GotoLine()
{
	int gotonum;
	cout << "��������ת�����кţ�";
	cin >> gotonum;
	if (gotonum <= 0 || gotonum > textbuffer.Length())
		return false;
	else
	{
		curLineNo = gotonum;
		return true;
	}
}

bool Editor::InsertLine()
{
	cout << "����������У�" << endl;
	string addline;
	getline(cin,addline);
	textbuffer.Insert(curLineNo + 1, addline);
	curLineNo++;
	return true;
}

void Editor::ChangeLine()
{
	char order;
	bool initialresponse = true;
	string oldstring, newstring;
	cout << "���滻��һ��(t)���滻ȫ����(a)��" << endl;
	do
	{
		order = getchar();
		order = tolower(order);
		initialresponse = false;
	} while (order != 't'&&order != 'a');

	cout << "������Ҫ���滻��ָ���ı�����" << endl;
	cin >> oldstring;
	cout << "��������д����ı���" << endl;
	cin >> newstring;

	for (int row = 1; row <= textbuffer.Length(); row++)
	{
		if (order == 't'&&row != curLineNo)
		{
			continue;
		}//����û�ҵ���ǰ��

		string str;
		textbuffer.GetElem(row, str);//����row�е�strRow�ҳ������ҷ���strRow��
		
		if (str.find(oldstring) != str.npos)
		//�˴�ʹ����string�е�find���������ҵ�ǰ�����Ƿ������Ҫ���滻���Ӵ�
		{
			int n = str.find(oldstring),len=oldstring.length();
			string newstr;
			newstr = str.replace(n,len, newstring);
			textbuffer.SetElem(row, newstr);
		}
	}
}

void Editor::FindString()
{
	char answer;
	bool initialResponse = true;
	do
	{
		if (initialResponse)
			cout << "�ӵ�һ�п�ʼf(irst)��ӵ�ǰ�п�ʼc(urrent):";
		else
			cout << "��f��c�ش�";
		answer = getchar();
		while (cin.get() != '\n');
		answer = tolower(answer);
		initialResponse = false;
	} while (answer != 'f'&&answer != 'c');
	if (answer == 'f')
		curLineNo = 1;

	int id;
	cout << "���뱻���ҵ��ı�����";
	string searchString;
	getline(cin, searchString);//�����ı���
	string curline;
	textbuffer.GetElem(curLineNo, curline);
	while (curline.find(searchString) == curline.npos)//û���ҵ�
	{
		if (curLineNo < textbuffer.Length())
		{
			curLineNo++;
			textbuffer.GetElem(curLineNo, curline);
		}
		else break;
	}
	if (curline.find(searchString) == curline.npos)//�����ж�û�в��Ҵ�
		cout << "���Ҵ�ʧ�ܣ�";
	else
	{
		cout << curLineNo<<":"<<curline << endl;
	}
	cout << endl;
}

void Editor::run()
{
	char userCommand;
	do
	{
		string tempstring;   //��ʱ��
		string curline;		//��ǰ��


		if (curLineNo != 0) //���ڵ�ǰ��
		{
			textbuffer.GetElem(curLineNo, curline);
			cout << "��ǰ���ǣ�"<<curLineNo << ":" << curline << endl;
		}//�����ǰ��
		else
			cout << "�ı�����Ϊ�ա�����h�򣿿ɻ�ò�������ʾ��" << endl;
		cin >> userCommand;//���������
		userCommand = tolower(userCommand); //��Сдת��
		while (cin.get() != '\n');

		if (userCommand != 'u'&&userCommand != 'h'&&userCommand != '?'&&userCommand != 'v')
		{
			textundobuffer = textbuffer;  //���ڳ����Ļ���
			curUndoLineNo = curLineNo;   //���ڳ������к�
		}
			switch (userCommand)
			{
			case 'b': //ת����һ��
				if (textbuffer.Empty())
					cout << "ע�⣺�ı�����Ϊ�գ�" << endl;
				else curLineNo = 1; 
				break;
			case 'c': //�滻��ǰ�л������е�ָ���ַ���
				if (textbuffer.Empty())
					cout << "ע�⣺�ı�����Ϊ�գ�" << endl;
				else ChangeLine(); 
				break; 
			case 'd'://ɾ����ǰ��
				if (textbuffer.Delete(curLineNo, tempstring) != true)
					cout << "����ɾ��ʧ�ܣ�" << endl;
					break;
			case 'e': 
				if (textbuffer.Empty())
					cout << "ע�⣺�ı�����Ϊ�գ�" << endl;
				else curLineNo = textbuffer.Length(); 
				break;
			case 'f':
				if (textbuffer.Empty())
					cout << "ע�⣺�ı�����Ϊ�գ�" << endl;
				else FindString(); 
				break;
			case 'g':
				if (GotoLine() != true)
					cout << "�����в�����!" << endl;
				break;
			case '?':
			case 'h':
				cout << "����:" << endl;
				cout << "b(egin) c(hange) d(elete) e(nd)" << endl;
				cout << "f(ind) g(o) h(elp) i(nsert) n(ext) p(rior)" << endl;
				cout << "q(uit) r(ead) u(ndo) v(iew) w(rite)" << endl;
				break;
			case 'i':
				if (InsertLine() != true)
					cout << "���󣺲����д���" << endl;
				break;
			case 'n':
				if (NextLine() != true)
					cout << "�����������һ��!" << endl;
				break;
			case 'p':
				if (PreviousLine() != true)
					cout << "�������ǵ�һ��!" << endl;
				break;
			case 'q':break;
			case 'r':ReadFile(); break;
			case 'u':
				swap(textundobuffer, textbuffer);
				swap(curLineNo, curUndoLineNo);
				break;
			case 'v':
				for (int i = 1; i <= textbuffer.Length(); i++)
				{
					string show;
					textbuffer.GetElem(i, show);
					cout << i << ":" << show << endl;
				}break;
			case 'w':WriteFile(); break;
			default: cout << "����h�򣿿ɻ����ʾ��������" << endl;
			}
	} while (userCommand != 'q');
}

void Editor::ReadFile()
{
	inFile.open(infName.c_str(), ios::in);
	string s;
	int i = 0;
	while (getline(inFile, s))
	{
		i++;
		textbuffer.Insert(i,s);
		curLineNo++;
	}
	cout<<"�ѳɹ������ļ���"<<endl; 
	inFile.close();
}

void Editor::WriteFile()
{
	
	outFile.open(outfName.c_str(), ios::out);
	for (int i = 1; i <= textbuffer.Length(); i++)
	{
		string str;
		textbuffer.GetElem(i, str);
		cout<<str<<endl;
		outFile << str <<endl;
	}
	cout << "�ѳɹ������ļ���" << endl;
	outFile.close();
}


/**************************************************/

int main()
{
	string in = "infile.txt", out = "outfile.txt";
	Editor a(in,out);
	a.run();
	return 0;
} 






 
 
 	//position ���ڷ�Χ��
/*	if (current == NULL)
	{
		current = first->rightlink = new DoubleNode<E>(value, first, first);
		count++;
		return true;
	}//����ͷ�ڵ�
	else
	{
		current = GetElemPtr(position);//currentָ���˴�����Ԫ�ص�λ��
		current->rightlink = new DoubleNode<E>(value, current, current->rightlink);//�޸����ҵ�ָ��
		current = current->rightlink;
		current->rightlink->leftlink = current;//�޸���ָ��
		curPosition = position;
		count++;
		return true;
	}*/
