class GenList;   //GenList���ǰ������
class GenListNode;//����������ǰ
������
struct Items {         //���н����Ϣ����
	friend class GenlistNode;
	friend class Genlist;
	int utype;                      //��0 / 1 / 2 / 3
	union { 	                                     //����
		int ref;       //utype=0, ������ü���
		int intinfo;	  //utype=1, �������ֵ 
		char charinfo; //utype =2, ����ַ�
		GenListNode *hlink;				       //utype =3, ���ָ���ӱ��ָ��
	}value;
}