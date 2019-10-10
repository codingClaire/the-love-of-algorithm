#include<iostream>
#include<string>
#include<set>
#include<map>
using namespace std;

//在定义数组时，其实是定义了一个从int型到int型的映射
//map可以将任何基本类型映射到任何基本类型（包括STL容器）
//判断给定的一些数字在某个文件中是否出现过
/*可以开一个bool型的hashTable[max_size]
通过判断hashTable[x]为true还是false来确定x是否在文件中出现过
问题是，数字可能很大，这个数组就开不了，此时map可以派上用场
可以把数字当成字符串，建立string到int的映射*/
int main()
{
    /*1.定义*/
    map<string,int> mp; //字符串到整型的映射必须要用string 不能用char数组
    map<set<int>, string> mp2;

    /*2.访问元素*/
    /*2.1 通过下标访问*/
    map<char,int> mp3;
    int tmp=mp3['c']; //map中的键值是唯一的
    mp3['c']=10;
    mp3['c']=20; //mp3['c']的值会被覆盖
    /*2.2 通过迭代器访问 */
    map<char,int>::iterator it;
    //it->first来访问键，it->second来访问值
    //map会以键从小到大的顺序自动排序（map）内部使用红黑树实现的

    /*3.查找键为key的映射的迭代器*/
    map<char,int>::iterator it= mp3.find('b');

    /*4.删除元素*/
    /*4.1 删除单个元素*/
    mp3.erase(it); //删除以it为迭代器的元素，时间复杂度O(1)
    char key='b';
    mp3.erase(key); //key为欲删除的映射的键，时间复杂度为O(logN)
    /*4.2 删除一个区间内的所有元素*/
    map<char,int>::iterator it_first,it_last;
    mp3.erase(it_first,it_last);//删除左闭右开的区间[it_first,it_last)    

    /*5.返回map中映射的对数*/
    int length=mp3.size();

    /*6.清空元素*/
    mp3.clear(); 

    /*map的常见用途：
    1.需要建立字符（字符串）与整数之间映射的题目
    2.判断大整数或者其他类型数据是否存在的题目，可以把map当bool数组用
    3.字符串和字符串的映射也有可能会遇到
    */
}

