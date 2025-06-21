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
bool InsertNextNode(LinkList *p,ElemType e)//指定结点的后插操作：在p结点后面插入元素e
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
        j++
    }
    return p; //i>表长，返回最后一个结点
}

LNode *LocateElem(LinkList L,ElemType e)//按值查找：某节点数据域=e,返回该结点
{
    LNode *P = L;//从第一个结点开始（没有头节点），否则应是L->next
    while(P != NULL && p->data != e)
        p=p->next;
    
    return p;  //找到后返回该结点，否则返回NULL(最后一个结点指向NULL)
}

