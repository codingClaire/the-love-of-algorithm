#include<set>
using namespace std;

set<int> number;
set<set<int> > number; 
//元素为set的set容器，>>中间要加空格，因为C++ 11之前标准的编译器会把它视为移位操作
set<int>::iterator it; //迭代器
int main()
{
    /*1.访问元素*/
    for(set<int>::iterator it=number.begin();it!=number.end();it++)
        printf("%d",*it);
    //set内的元素自动递增排序，且会去除重复元素

    /*2.插入元素*/
    int x;
    number.insert(x);
    //将x插入number中，并自动递增排序和去重，时间复杂度O(lgN)

    /*3.返回指定值的迭代器(下标）*/
    int value=3;
    set<int>::iterator it_value_is_three=number.find(value);
    int v=*it_value_is_three; //下标值

    /*4.删除元素*/
    /*4.1 删除单个元素*/
    number.erase(it_value_is_three);//删除迭代器，时间复杂度O(1)
    number.erase(value); //删除值为value的元素 O(logN)
    /*4.2 删除区间内的所有元素*/
    set<int>::iterator it_first,it_last;
    number.erase(it_first,it_last);
    //删除的是[it_first,it_last)中的元素，时间复杂度为O(it_last-it_first)

    /*5.返回元素的个数*/
    int w=number.size();

    /*6.清空所有的元素*/
    number.clear();

    //set主要是自动去重，按升序排序
    //set中的元素是唯一的，如果需要处理不唯一的情况，则需要使用multiset

    return 0;
}
