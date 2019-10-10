#include<string>
#include<iostream>
using namespace std;

int main()
{
    /*1.定义string*/
    string str;
    str="abcd"; 

    /*2.访问string中的内容*/
    /*2.1 通过下标*/
    char a=str[1];
    /*2.2 通过迭代器访问*/
    string::iterator it; //迭代器支持直接加/减某个数字
    for(it=str.begin();it!=str.end();it++)
        printf("%c",*it);

    /*3.链接字符串*/
    string str1="aaa",str2="bbb";
    str=str1+str2;

    /*4.比较字符串*/
    //两个string类型可以直接使用== != < <= > >=比较大小，是按照字典序
    if(str1<str2)
        printf("smaller");
    
    /*5.字符串的长度*/
    int w1=str.length();
    int w2=str.size();
    //length和size是基本相同的

    /*6.插入字符串*/
    /*6.1 在pos位置插入字符串str*/
    string newstr;
    int pos;
    str.insert(pos,newstr);
    /*6.2 全部使用迭代器表示*/
    string::iterator it_first,it_last;
    str.insert(it,it_first,it_last);
    //it为原字符串欲插入位置，it2和it3为待插入字符串的首尾迭代器[it_first,it_first)

    /*7.删除字符串*/
    /*7.1 删除单个元素*/
    str.erase(it);
    /*7.2 删除区间内的所有元素*/
    str.erase(it_first,it_last); //删除[it_first,it_last)的所有元素
    int length;
    str.erase(pos,length); //从pos开始删除，长度为length


    /*8.清空字符串*/
    str.clear();

    /*9.截取子序列*/
    string sub=str.substr(pos,length);

    /*10.查询子串*/
    if(str.find(sub)!=string::npos)//当sub是str的子串时，返回在str第一次出现的位置，如果不是则返回string::npos
        cout<<"we can find substring"<<endl;
    //string::npos 是一个常数，本身的值为-1，但由于是unsigned_int类型，也可以认为是unsigned_int类型的最大值4294967295
    //当find失配时，返回的即是string::npos
    if(str.find(sub,pos)!=string::npos)//从str的pos号位开始匹配sub
        cout<<"we can find substring from position %d"<<pos<<endl;
    //时间复杂度位O(nm),n和m分别位str和sub的长度

    /*11.替换字串*/
    str.replace(pos,length,sub); //把str从pos号位开始、长度为length的子串替换为sub
    str.replace(it_first,it_last,sub); //把str的迭代器[it_first,it_last)范围的字串替换为sub

    return 0;
}