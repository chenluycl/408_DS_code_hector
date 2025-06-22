#include<iostream>
#include<cstdlib>

using namespace std;

typedef int ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;

bool InitList(LinkList &L)//初始化一个单链表，不带头节点
{
    L=NULL;
    return true;
}

// bool InitList(LinkList &L) //带头节点初始化链表
// {
//     L=(LNode *)malloc(sizeof(LNode));
//     L->next=NULL;
//     return true;
// }

bool Empty(LinkList L)//单链表判空
{
    if(L==NULL)
        return true;
    else return false;
}

//malloc 在堆（heap）上动态分配内存来创建一个新的链表节点
//会返回一个指向这块内存起始地址的通用指针，类型是 void *（无类型指针）
//如果内存分配失败，malloc 会返回 NULL (或 nullptr)
//(LNode *)：这是一个强制类型转换 (type cast)
//因为 malloc 返回的是 void * 类型的指针,需要将 void * 显式地转换成 LNode *
bool InsertNextNode(LNode *p,ElemType e)//指定结点的后插操作：在p结点后面插入元素e
{
    if(p==NULL)
        return false;
    LNode *s=(LNode *)malloc(sizeof(LNode));

    if(s==NULL)
        return false;
    
    //后插结点操作，三部曲：先存值，再修改两次指针
    s->data=e;
    s->next=p->next;
    p->next=s;
    
    return true;
}

bool InsertPriorNode(LNode *p, ElemType e)//指定结点的前插操作：在p结点前面插入元素e
{
    if(p==NULL)
        return false;
    LNode *s=(LNode *)malloc(sizeof(LNode));
    if(s==NULL)
        return false;
    
    //实际上实现不了前插（找不到前一个结点来后插）
    //只不过可以：仍然执行后插，最后交换两个结点的值，变相实现了前插
    s->next=p->next;
    p->next=s;
    s->data=p->data;
    p->data=e;//e覆盖p的数据域

    return true;
}

LNode *GetElem(LinkList L,int i)//按位（位序）查找：返回第i个结点
{
    if(i<1) // 没有判断i>表长
        return NULL;
    LNode *p=L;
    int j=0;
    while(p != NULL && j < i) 
    {
        p=p->next;
        j++;
    }
    return p; //i>表长，返回最后一个结点
}

LNode * LocateElem(LinkList L,ElemType e)//按值查找:第一个数据域=e的结点,返回该结点
{
    LNode *p = L;//从第一个结点开始（没有头节点），否则应是L->next
    while(p != NULL && p->data != e)
        p=p->next;
    
    return p;  //找到后返回该结点，否则返回NULL(最后一个结点指向NULL)
}

bool LinkInsert(LinkList &L,int i,ElemType e)//按位序插入操作，第i个位置（即第i-1个结点后）插入指定元素e
{
    if(i<1) 
        return false;
    
    //不带头节点，需要额外处理
    if(i==1)
    {
        LNode *s=(LNode *)malloc(sizeof(LNode));
        if(s==NULL)
            return false;
        s->data=e;
        s->next=L;
        L=s; //头指针指向新结点
        return true;
    }

    LNode *p=L;
    int j=1;
    while(p != NULL && j<i-1) //找到第i-1个结点
    {
        p=p->next;
        j++;
    }//若找到了，退出循环时，j=i-1，即p指向第i-1个结点
    if(p==NULL) //i值不合法
        return false;

    LNode *s=(LNode *)malloc(sizeof(LNode));
    s->data=e;
    s->next=p->next;
    p->next=s;

    return true;
}

bool ListDelete(LinkList &L,int i,ElemType &e)//按位序删除操作：删除链表中第i个结点，并用e返回结点的值
{
    if(i<1) 
        return false;
    if(i==1) //删除第一个结点（无头节点）
    {
        LNode *s=L;
        e=s->data;
        L=s->next;
        free(s);
        return true;
    }

    LNode *p=L;//用p来遍历，直到找到第i-1个链表
    int j=1;
    while(p != NULL && j<i-1)
    {
        p=p->next;
        j++;
    }//找到了， p=i-1
    if(p==NULL)
        return false;

    if(p->next == NULL)//第i-1个结点后面没有其他结点，无法删除
        return false;

    LNode  *s=p->next; //s指向第i个结点
    e=s->data;
    p->next=s->next;
    free(s);
    return true;
/*
    //带头结点的写法
    LNode *p=L;
    int j=0;
    while(p->next != NULL && j < i-1)
    {
        p=p->next;
        j++;
    }
    if(p->next == NULL || j > i-1)//i值不合法
        return false; 

    LNode *s=p->next;
    e=s->data;
    p->next=s.next;
    free(s);
*/
}

bool DeleteNode(LNode *p)//指定结点删除，删除指定结点p
{
    if(p == NULL)
        return false;
    
    //通常是，找到p的前驱，然后执行删除p
    //巧妙的方法：将p的后继的值赋给p，再删除p的后继
    LNode *s=p->next;
    p->next=s->next;
    //但是当p是最后一个结点，s=NULL,执行s->next会报错，只能从第一个结点找到p的前驱，然后执行普通删除操作
    p->data=p->next->data;
    free(s);

    return true;
}

int Length(LinkList L)//求表长
{
    int len = 0;
    LNode *p = L;
    while(p != NULL)
    {
        p=p->next;
        len++;
    }//当p==NULL时，退出循环
    return len;
}

LinkList List_TailInsert(LinkList &L)//尾插法建立单链表
{
    ElemType e;
    InitList(L);//初始化单链表

    LNode *s,*r=L;//r为表尾指针
    cout<<"输入结点值，-1表示退出:\n";
    cin>>e;
    while (e != -1)
    {
        s=(LNode *)malloc(sizeof(LNode));
        if(s == NULL)
            return NULL;
        s->data=e;
        if(r == NULL)//处理第一个结点时，需要做结点迁移（没有头结点的特殊处理）
            L=s;
        else r->next=s;
        r=s;//用s来更新r
        cin>>e;
    }
    r->next=NULL;//表尾指空
    
    return L;
}

bool List_HeadInsert(LinkList &L)//头插法建立单链表
{
    ElemType e;
    InitList(L);

    LNode *s;
    
    cin>>e;
    while(e != -1)
    {
        s=(LNode *)malloc(sizeof(LNode));
        if(s==NULL)
            return NULL;
        s->data=e;
        if(L == NULL) //处理第一个结点
            s->next=NULL;
        else 
            s->next=L->next;
        L=s;  //若有头结点，就是L->next=s;
        cin>>e;
    }
    return L;
}

void PrintList(LinkList L)
{
    LNode *p=L;
    cout<<"当前链表：";
    while(p != NULL) //有头结点：p->next != NULL
    {
        cout<<p->data<<' ';
        p=p->next;
    }
    cout<<'\n';
}

void DestoryList(LinkList &L)//释放单链表，递归
{
    if(L != NULL)
    {
        DestoryList(L->next);
        free(L);
    }
}

//删除所有值为e的结点，保证删除后单链表的连续性
LinkList Delete_same(LinkList &L,ElemType e)//递归删除
{
    LNode *p;
    if(L == NULL) //递归结束条件
        return NULL;
    if(L->data == e)//当前结点值为e,要被删除
    {
        p=L;
        L=L->next; //后移L
        free(p);
        return Delete_same(L,e);
    }
    else//值不是e，则判断它的下一个结点
    {
        //将后面修改后的结果接在当前位置
        L->next=Delete_same(L->next,e);//回溯过程重新连接单链表
        return L;
    }
}

void Test()
{
    cout<<"建立单链表：\n";
    LinkList L; 
    List_TailInsert(L); //尾插法建立
    /*
        1 2 3 4 5 6 4 8 9 4 29 -1
    */
    PrintList(L);

    // L=Delete_same(L,4);
    // PrintList(L);

    LNode *p = LocateElem(L,4);
    cout<<p->data<<'\n';

    DestoryList(L);
}

int main()
{
    cout<<"程序开始：\n\n";
    Test();
    cout<<"\n运行完成,程序退出 ^_^\n";
    return 0;
}