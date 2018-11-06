class GenList;   //GenList类的前视声明
class GenListNode;//广义表结点类的前
视声明
struct Items {         //仅有结点信息的项
	friend class GenlistNode;
	friend class Genlist;
	int utype;                      //＝0 / 1 / 2 / 3
	union { 	                                     //联合
		int ref;       //utype=0, 存放引用计数
		int intinfo;	  //utype=1, 存放整数值 
		char charinfo; //utype =2, 存放字符
		GenListNode *hlink;				       //utype =3, 存放指向子表的指针
	}value;
}