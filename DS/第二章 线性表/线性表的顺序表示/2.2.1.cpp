#include<iostream>
#include<cstdlib>
#include<climits>
using namespace std;

#define MaxSize 50

typedef int ElemType;

typedef struct  //顺序表定义
{
    ElemType data[MaxSize];
    int length;
}Sqlist; 

void InitList(Sqlist &L)//初始化
{
    // for(int i=0;i<MaxSize;i++)
    //     L.data[i]=0;
    L.length=0;
}

//位序从1开始，数组下标从0开始
bool ListInsert(Sqlist &L,int i,ElemType e)//插入操作，第i个位置元素e
{
    if(i<1||i>L.length+1) 
        return false;
    if(L.length>=MaxSize) //当前存储空间满，不能插入
        return false;

    for(int j=L.length;j>=i;j--)
        L.data[j]=L.data[j-1];
    
    L.data[i-1]=e;
    L.length++;
    return true;
}

bool ListDelete(Sqlist &L,int i ,ElemType &e)//删除操作,e返回被删除元素的值
{
    if(i<1||i>L.length+1) 
        return false;

    e=L.data[i-1];
    for(int j=i-1;j<L.length;j++)
        L.data[j]=L.data[j+1];
    L.length--;
    return true;
}

ElemType GetElem(Sqlist L,int i)//按位查找
{
    if(i>=1&&i<=L.length+1) 
        return L.data[i-1];
    else return INT_MIN;//-2147483638
}

int LocateElem(Sqlist L,ElemType e)//按位查找第一个值为e的位置
{
    for(int i=0;i<L.length;i++)   
        if(L.data[i]==e)
            return i+1;
    return -1;
}

int GetLength(Sqlist L)//获取线性表的长度
{
    return L.length;
}

void PrintList(Sqlist L)//打印线性表的元素
{
    cout<<"当前线性表：";
    for(int i=0;i<L.length;i++)
        cout<<L.data[i]<<' ';
    cout<<'\n';
}


bool Empty(Sqlist L)//判断线性表是否为空
{
    return L.length==0;
}

bool DestoryList(Sqlist &L)
{
    return true;//由于是数组不可以销毁
}

//删除最小元素，并返回其值，用最后一个元素填补,若为空表则报错
bool Delete_MinElem(Sqlist &L,ElemType &e)
{
    if(L.length==0)
    {   cout<<"顺序表为空,无法进行删除！/n";
        return false;
    }
    //找到最小的位置
    int min_pos=0;
    for(int i=0;i<L.length;i++)
        if(L.data[i]<=L.data[min_pos])
            min_pos=i;
        
    e=L.data[min_pos];
    L.data[min_pos]=L.data[L.length-1]; //最后一个元素填补
    L.length--;

    return true;
}

void Test()
{
    Sqlist L;

    InitList(L);

    ListInsert(L,1,5); ListInsert(L,2,4); ListInsert(L,2,6);
    ListInsert(L,1,2); ListInsert(L,2,10); ListInsert(L,3,9); 
    ListInsert(L,5,10);//2 10 9 5 10 6 4 

    PrintList(L);
    ElemType num;
    cout<< "删除值最小的元素,(1表示成功,0表示失败):"<<Delete_MinElem(L,num)<<'\n';
    cout<<"被删除的最小元素："<<num<<'\n';

    PrintList(L);

}
int main() {

    Test();
    return 0;
}




