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
	//声明为友元函数，让DoubleLinkList中的成员函数可以调用DoubleNode中的私有成员
private:
	E data; //元素值
	DoubleNode<E> *leftlink, *rightlink; //左指针，右指针
	DoubleNode(E value, DoubleNode<E> *left, DoubleNode<E> *right) :data(value), leftlink(left), rightlink(right) {}
	DoubleNode(E value) :data(value), leftlink(NULL), rightlink(NULL) {}
	DoubleNode(){}
	//两个构造函数
};

template<class E> class DoubleLinkList
{
public:
	DoubleLinkList(E val); //构造函数
	DoubleLinkList();
	virtual ~DoubleLinkList() {}; //析构函数
	int Length(); //求双向链表的长度
	bool Empty() { return first->rightlink == first; } //判断是否为空
	bool Find(const E& target);//给定元素的查找

	int CurrentPosition() const { return curPosition; } //返回当前位置
	bool GetElem(int position, E& get); //返回位置为position的元素
	bool SetElem(int position, const E &e); //设定位置为position的元素值
	bool Insert(int position, const E &value); //插入元素
	bool Delete(int position, E &e); //删除元素
	bool First(); //取第一个元素
	bool Next(); // 取下一个元素
	bool Prior(); //取上一个元素
	void Init();//初始化双向链表
protected:
	DoubleNode<E> *first, *current; //first头节点指针 current指向当前结点的指针
	int curPosition;//当前结点的位置
	int count;//元素的总个数
			  /*辅助函数*/
	DoubleNode<E> *GetElemPtr(int position);//返回指向第position个结点的指针
	
};

template<class E>
DoubleNode<E>* DoubleLinkList<E>::GetElemPtr(int position)
{
	if (curPosition < position)
	{	// 当前位置在所查找位置之前,向后查找
		while (curPosition < position)
		{
			current = current->rightlink;
			curPosition++;
		}
	}
	else if (curPosition>position)
	{	// 当前位置在所查找位置之后,向前查找
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
	first = new DoubleNode<E>; //构造头指针
	first->leftlink = first;
	first->rightlink = first;//双向循环链表的头指针前驱和后继均为头节点本身
	curPosition = 0;//当前位置坐标为0
	current = first;//并且当前指针也指向头节点
	count = 0;//元素总个数为0
}

template<class E>
bool DoubleLinkList<E>::Find(const E &target)
{
	DoubleLinkList<E> *p = first->rightlink;
	while (p != first&&p->data != target)//不空且没有找到
	{
		p = p->rightlink;
	}
	if (p != first)
	{
		current = p;
		return true; //成功找到 并且修改current指针 使其指向要寻找的值
	}
	return false;//查找失败
}

template<class E>
bool DoubleLinkList<E>::Insert(int position, const E &value)
{
	
	if (position<1 || position>Length() + 1)
		return false;
	else
	{	// position合法
		DoubleNode<E> *tmpPtr, *nextPtr, *newPtr;
		tmpPtr = GetElemPtr(position - 1);	// 取出指向第position-1个结点的指针
		nextPtr = tmpPtr->rightlink;				// nextPtr指向第position个结点	
		newPtr = new DoubleNode<E>(value, tmpPtr, nextPtr);// 生成新结点
		tmpPtr->rightlink = newPtr;				// 修改向右的指针
		nextPtr->leftlink = newPtr;				// 修改向左的指针
		curPosition = position;				// 设置当前位置的序号
		current = newPtr;					// 设置指向当前位置的指针
		count++;							// 插入成功后元素个数加1 
		return true;
	} 
}

template<class E>
bool DoubleLinkList<E>::Delete(int position,E &e)
{//删除结点
	if (position<1 || position>Length())
		return false;//position的范围错误
	else //if (current != NULL)
	{
		current = GetElemPtr(position - 1);
		current = current->rightlink;
		current->rightlink->leftlink = current->leftlink;
		current->leftlink->rightlink = current->rightlink;
		//current = current->rightlink;
		e = current->data;
		if (position == Length())//删除的是最后一个结点 current 此时指向了first
		{
			curPosition = 0;
			current = first;
		}
		else
		{
			curPosition = position;
			current = current->rightlink;
			//双向循环链表 有头节点 此时要将current指向第一个元素（非头节点)
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
{//求双向链表的长度
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
{//current指向第一个元素（第一个元素访问）
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
{//访问下一个元素
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
{//访问上一个元素
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
// 操作结果：当线性表存在第position个元素时，用e返回其值
{
	if (position < 1 || position > Length())
		return false;
	else
	{	// position合法
		DoubleNode<E> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// 取出指向第position个结点的指针	
		e = tmpPtr->data;				// 用e返回第position个元素的值
		return true;
	}
}

template <class E>
bool DoubleLinkList<E>::SetElem(int position, const E &e)
// 将线性表的第position个位置的元素赋值为e,
//	position的取值范围为1≤position≤Length()
{
	if (position < 1 || position > Length())
		return true;
	else
	{	// position合法
		DoubleNode<E> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// 取出指向第position个结点的指针
		tmpPtr->data = e;				// 设置第position个元素的值
		return true;
	}
}
/**************************************************/
class Editor
{
private:
	DoubleLinkList<string> textbuffer; //文本缓存（双向循环链表）
	int curLineNo;//当前行号
	DoubleLinkList<string> textundobuffer; //恢复文本缓存（双向循环链表）
	int curUndoLineNo;//恢复的当前行号
	ifstream inFile; //输入文件
	ofstream outFile; //输出文件
	string infName, outfName;
	bool NextLine(); //转到下一行
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
		cout << "下一行是:" << nextline << endl;
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
		cout << "上一行是：" << previousline << endl;
		return true;
	}
}

bool Editor::GotoLine()
{
	int gotonum;
	cout << "请输入跳转到的行号：";
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
	cout << "请输入添加行：" << endl;
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
	cout << "仅替换这一行(t)或替换全部行(a)？" << endl;
	do
	{
		order = getchar();
		order = tolower(order);
		initialresponse = false;
	} while (order != 't'&&order != 'a');

	cout << "请输入要被替换的指定文本串：" << endl;
	cin >> oldstring;
	cout << "请输入新写入的文本串" << endl;
	cin >> newstring;

	for (int row = 1; row <= textbuffer.Length(); row++)
	{
		if (order == 't'&&row != curLineNo)
		{
			continue;
		}//当还没找到当前行

		string str;
		textbuffer.GetElem(row, str);//将第row行的strRow找出来并且放入strRow中
		
		if (str.find(oldstring) != str.npos)
		//此处使用了string中的find函数，查找当前行中是否存在需要被替换的子串
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
			cout << "从第一行开始f(irst)或从当前行开始c(urrent):";
		else
			cout << "用f或c回答：";
		answer = getchar();
		while (cin.get() != '\n');
		answer = tolower(answer);
		initialResponse = false;
	} while (answer != 'f'&&answer != 'c');
	if (answer == 'f')
		curLineNo = 1;

	int id;
	cout << "输入被查找的文本串：";
	string searchString;
	getline(cin, searchString);//输入文本串
	string curline;
	textbuffer.GetElem(curLineNo, curline);
	while (curline.find(searchString) == curline.npos)//没有找到
	{
		if (curLineNo < textbuffer.Length())
		{
			curLineNo++;
			textbuffer.GetElem(curLineNo, curline);
		}
		else break;
	}
	if (curline.find(searchString) == curline.npos)//所有行都没有查找串
		cout << "查找串失败！";
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
		string tempstring;   //临时串
		string curline;		//当前行


		if (curLineNo != 0) //存在当前行
		{
			textbuffer.GetElem(curLineNo, curline);
			cout << "当前行是："<<curLineNo << ":" << curline << endl;
		}//输出当前行
		else
			cout << "文本缓存为空。输入h或？可获得操作符提示！" << endl;
		cin >> userCommand;//输入操作符
		userCommand = tolower(userCommand); //大小写转换
		while (cin.get() != '\n');

		if (userCommand != 'u'&&userCommand != 'h'&&userCommand != '?'&&userCommand != 'v')
		{
			textundobuffer = textbuffer;  //用于撤销的缓存
			curUndoLineNo = curLineNo;   //用于撤销的行号
		}
			switch (userCommand)
			{
			case 'b': //转到第一行
				if (textbuffer.Empty())
					cout << "注意：文本缓存为空！" << endl;
				else curLineNo = 1; 
				break;
			case 'c': //替换当前行或所有行的指定字符串
				if (textbuffer.Empty())
					cout << "注意：文本缓存为空！" << endl;
				else ChangeLine(); 
				break; 
			case 'd'://删除当前行
				if (textbuffer.Delete(curLineNo, tempstring) != true)
					cout << "错误：删除失败！" << endl;
					break;
			case 'e': 
				if (textbuffer.Empty())
					cout << "注意：文本缓存为空！" << endl;
				else curLineNo = textbuffer.Length(); 
				break;
			case 'f':
				if (textbuffer.Empty())
					cout << "注意：文本缓存为空！" << endl;
				else FindString(); 
				break;
			case 'g':
				if (GotoLine() != true)
					cout << "错误：行不存在!" << endl;
				break;
			case '?':
			case 'h':
				cout << "命令:" << endl;
				cout << "b(egin) c(hange) d(elete) e(nd)" << endl;
				cout << "f(ind) g(o) h(elp) i(nsert) n(ext) p(rior)" << endl;
				cout << "q(uit) r(ead) u(ndo) v(iew) w(rite)" << endl;
				break;
			case 'i':
				if (InsertLine() != true)
					cout << "错误：插入行错误！" << endl;
				break;
			case 'n':
				if (NextLine() != true)
					cout << "错误：这是最后一行!" << endl;
				break;
			case 'p':
				if (PreviousLine() != true)
					cout << "错误：这是第一行!" << endl;
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
			default: cout << "输入h或？可获得提示符帮助！" << endl;
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
	cout<<"已成功读入文件！"<<endl; 
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
	cout << "已成功保存文件！" << endl;
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






 
 
 	//position 不在范围内
/*	if (current == NULL)
	{
		current = first->rightlink = new DoubleNode<E>(value, first, first);
		count++;
		return true;
	}//插入头节点
	else
	{
		current = GetElemPtr(position);//current指向了待插入元素的位置
		current->rightlink = new DoubleNode<E>(value, current, current->rightlink);//修改向右的指针
		current = current->rightlink;
		current->rightlink->leftlink = current;//修改左指针
		curPosition = position;
		count++;
		return true;
	}*/
