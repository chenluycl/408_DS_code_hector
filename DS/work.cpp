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

//逆置链表，空间复杂度（1）
bool Reverse_List(Sqlist &L)
{
    ElemType temp;
    for(int i=0;i<L.length/2;i++)
        {
            temp=L.data[i];
            L.data[i]=L.data[L.length-i-1];
            L.data[L.length-i-1]=temp;
        }

    return true;
}

//2.2.3 删除表中值为x的元素
void Delete_val_x(Sqlist &L,ElemType x)
{
    int k=0;
    for(int i=0;i<L.length;i++)
    {
        if(L.data[i]==x)
            k++;
        else
            L.data[i-k]=L.data[i];
    }
    L.length-=k;  // 注意表长也要修改

}

//2.2.4 删除表中 s <= x <= t 的所有元素x，s<t,空表报错
bool Dlete_s_t(Sqlist &L,ElemType s,ElemType t)
{
    int k=0;
    if(s>=t||L.length==0)
        return false;
    
    for(int i=0;i<L.length;i++)
    {
        if(L.data[i] >=s && L.data[i] <= t)
            k++;
        else L.data[i-k]=L.data[i];
    }
    L.length-=k;
    return true;
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
    //空间复杂度O(p), 额外借助长度为p的一位数组
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

    ListInsert(L,1,5);
    ListInsert(L,2,4);
    ListInsert(L,2,6);
    ListInsert(L,1,2);
    ListInsert(L,2,10);
    ListInsert(L,3,9); 
    ListInsert(L,5,10);//2 10 9 5 10 6 4 

    PrintList(L);
    // int delete_pos=4,delete_e;
    // ListDelete(L,delete_pos,delete_e);
    // cout<<"删除第"<<delete_pos<<"位置的元素,值为："<<delete_e<<endl;

    // PrintList(L);
    // ElemType num;
    // cout<< "删除值最小的元素,(1表示成功,0表示失败):"<<Delete_MinElem(L,num)<<'\n';
    // cout<<"被删除的最小元素："<<num<<'\n';

    // PrintList(L);

    // Reverse_List(L);cout<<"逆置顺序表后,";

    // PrintList(L);

    // ElemType x=10;
    // Delete_val_x(L,x);cout<<"删除值为"<<x<<"的元素,";
    // PrintList(L);


    // ElemType s,t;
    // cin>>s>>t;
    // if(Dlete_s_t(L,s,t))
    //     {cout<<"删除值大于等于"<<s<<"小于等于"<<t<<"的所有元素，";
    //         PrintList(L);
    //     }
    // else 
    //     cout<<"删除失败\n";

    int p=3;
    PrintList(L);
    Move_p(L,p);cout<<"循环左移"<<p<<"个位置，";
    PrintList(L);

}
int main() {

    Test();
    return 0;
}