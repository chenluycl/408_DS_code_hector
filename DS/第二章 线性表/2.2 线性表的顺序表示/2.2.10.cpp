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


//2.1.10 将一维数组中的元素，循环左移P个位置  X0,X1,...,Xn-1 --> Xp,Xp+1,...,Xn-1,X0,X1,...,Xp
void Move_p(Sqlist &L,int p)
{
    Sqlist T;       //辅助数组，长度为p
    InitList(T);
    T.length=p;

    for(int i=0;i<p;i++)  //存下前p个元素
        T.data[i]=L.data[i];

    for(int i=p;i<L.length;i++) //剩余的n-p个元素前移
        L.data[i-p]=L.data[i];

    for(int i=L.length-p,j=0;j<p;j++,i++) // 前p个元素覆盖L的后p个位置
        L.data[i]=T.data[j];

    //时间复杂度O(n+P)
    //空间复杂度O(p), 额外借助长度为p的一维数组
}

//2.1.10 答案：时间复杂度O(n),空间复杂度O(1)
void Reverse(Sqlist &L,int from,int to) // 逆置from到to中间的元素
{
    for(int i=from-1,i<(to-from)/2,i++)
        L.data[i]=L.data[from+to-2-i];
    
}

void Converse(Sqlist &L,)


void Test()
{
    Sqlist L;

    InitList(L);

    ListInsert(L,1,5); ListInsert(L,2,4); ListInsert(L,2,6);
    ListInsert(L,1,2); ListInsert(L,2,10); ListInsert(L,3,9); 
    ListInsert(L,5,10);//2 10 9 5 10 6 4 

    PrintList(L);

    int from=2,to=5;
    Reverse(L,from,to);
    PrintList(L);
}
int main() {

    Test();
    return 0;
}