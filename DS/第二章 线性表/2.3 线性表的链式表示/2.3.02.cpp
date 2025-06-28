#include<iostream> //带头结点
#include<cstdlib>

using namespace std;

typedef int ElemType;

typedef struct LNode{ 
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

bool InitList(LinkList &L)//初始化一个单链表(带头结点)
{
    L=(LNode *)malloc(sizeof(LNode));
    if(L==NULL)
        return false;
    L->next=NULL;
    return true;
}

 bool Empty(LinkList L)//单链表判空
 {
    if(L->next==NULL)
        return true;
    else return false;
 }

bool InsertNextNode(LNode *p,ElemType e)//指定结点的后插:在p结点后面插入元素e
{
    if(p==NULL)
        return false;
    LNode *s=(LNode *)malloc(sizeof(LNode));

    s->data=e;
    s->next=p->next;
    p->next=s;

    return true;
}

bool InsertPrioriNode(LNode *p,ElemType e)//指定结点的前插操作：在p结点的前面插入元素e
{
    if(p==NULL)
        return false;
    LNode *s=(LNode *)malloc(sizeof(LNode));

    //在p后面插入，再交换p,s数据域的值
    s->next=p->next;
    p->next=s;
    s->data=p->data;
    p->data=e;
    return true;
}

LNode *GetElem(LinkList L,int i)//按位查找操作:返回第i个结点
{
    if(i<0)
        return nullptr;
    LNode *p=L;//定义临时指针指向表头,用于遍历
    int j=0;
    while(L->next != NULL && j<i)
    {
        p=p->next;
        j++;
    }//出循环,j=i
    
    return p;
}

LNode *LocateElem(LinkList L,ElemType e)//按值查找操作：找到数据域==e的结点
{
    LNode *p=L->next;
    while(p->next != NULL && p->data != e)
        p=p->next;
    return p;
}

bool ListInsert(LinkList &L,int i,ElemType e)//按位序插入操作：在表L中第i个位置插入指定元素e
{
    if(i<0) 
        return false;
    //循环找到第i-1个结点(链表不能随机存取,只能循环遍历到第i-1个结点)
    LNode *p=L; //p指向头结点,头结点是第0个结点
    int j=0;
    while(p->next != NULL && j < i)
    {
        p=p->next;
        j++;
    }//j=i-1

    if(p==NULL)//i值不合法,i>表长
        return false;
    LNode *s=(LNode *)malloc(sizeof(LNode));
    s->data=e;
    s->next=p->next;
    p->next=s;

    return true;
}

bool ListInsert_short(LinkList &L,int i,ElemType e)//按位序插入操作:封装版本
{
    if(i<0) return false;
    LNode *p=GetElem(L, i-1);//返回第i-1个结点的位置，赋值给临时变量p
    return InsertNextNode(p,e);
}

bool ListDelete(LinkList &L,int i,ElemType &e)//按位序删除操作:删除表L中第i个结点,并用e返回删除结点的值
{
    if(i < 0) return false;
    LNode *p=L;
    int j=0;
    while(p->next != NULL && j < i)
    {
        p=p->next;
        j++;
    }//j=i-1
    if(p==NULL)//i值不合法
        return false;  
    if(p->next == NULL)//第i-1是最后一个结点
        return false;

    LNode *s=p->next;
    e=s->data;
    p->next=s->next;
    free(s);
    return true;

    //p->next=p->next->next;如果不引入结点s指向p的下一个结点
}

bool DeleteNode(LNode *p)//指定结点的删除操作：删除指定结点p
{
    //由于无法知道p的前驱，思想与前插法一样
    //将p的后继结点的值赋值给p,然后删除p的后继结点
    if(p=NULL) return false;
    LNode *s=p->next;
    p->next=s->next; //将s从链中断开
    p->data=s->data;
    free(s);

    return true;
}

int Length(LinkList L)//求表长
{
    int len=0;
    LNode *p=L;//p指向头结点（第0个结点），需要用p->next != null 判断
    while(p->next != nullptr)
    {
        p=p->next;
        len++;
    }

    // LNode *p=L->next;//如果p指向第1个结点,则使用p != null 判断
    // while(p != nullptr)
    // {
    //     p=p->next;
    //     len++;
    // }
    return len;
}

LinkList List_TailInsert(LinkList &L)//尾插法建立单链表
{
    ElemType e;
    if(InitList(L)==false)
        return nullptr;
    
    LNode *s,*r=L;//r为表尾指针
    cin>>e;
    while(e != -1)
    {
        s=(LNode *)malloc(sizeof(LNode));
        if(s==nullptr) return nullptr;
        s->data=e;
        r->next=s;
        r=s;//更新r

        cin >> e;
    }
    r->next=nullptr;//尾结点的next指向空
    return L;
}

LinkList List_HeadInsert(LinkList &L)//头插法建立单链表
{
    if(InitList(L) == false) return nullptr;
    ElemType e;
    LNode *s;
    cin>>e;
    while(e != -1)
    {
        s=(LNode *)malloc(sizeof(LNode));
        if(s==nullptr) return nullptr;
        s->data=e;
        s->next=L->next;//不能写成L,L是头结点，不是第一个结点
        L->next=s;//同理，头指针的next指向s
    }
    return L;
}

void PrintList(LinkList L)//打印单链表
{
    LNode *p=L->next;
    while(p != nullptr)
    {
        cout<<p->data<<' ';
        p=p->next;
    }
    cout<<'\n';

    /* 
    另一种写法，推荐使用上面的写法
    LNode *p=L;
    while(p->next != nullptr)
    {
        cout<<p->data<<' ';
        p=p->next;
    }
    */
}

void My_DeleteList(LinkList &L)
{
    LNode *p=L;
    LNode *temp=nullptr;
    while(p != nullptr)
    {
        temp=p->next;
        free(p);
        p=temp;
    }
    L=nullptr;
}


void DestoryList(LinkList &L)//释放单链表
{
    if(L != NULL)
    {
        DestoryList(L->next);
        free(L);
    }
    //L->next==null时，递归回溯
}

// void Delete_Same(LinkList &L,ElemType e)
// {
//     LNode *p=L->next,*pre=L;
//     LNode *q;//临时变量用来释放

//     while(p!=nullptr)
//     {
//         if(p->data == e)//让p移向下一个结点
//         {
//             q=p;//临时存储p的地址
//             pre->next=p->next;
//             p=p->next;
//             free(q);
//         }
//         else
//         {
//             pre=p;
//             p=p->next; // 好像没有判断p的next是否存在？
//         }
//     }
// }

void Delete_Same(LinkList &L,ElemType e)//采用尾插法建立单链表：值!=e的结点重新链接到L之后
{
    LNode *p=L->next,*r=L;
    LNode *q;
    while(p != nullptr)
    {
        if(p->data == e)
        {
            q=p;
            p=p->next;
            free(q);
        }
        else //关键:借助r,从L出重新建立单链表（排除值为e的元素）
        {
            r->next=p;
            r=p;
            p=p->next;
        }
    }
}

void Test()
{
    LinkList L;
    List_TailInsert(L); 
    /*
    
    */
    PrintList(L);

    Delete_Same(L,3);

    PrintList(L);

    DestoryList(L);
}

int main()
{
    cout<<"begin...\n";
    Test();
    cout<<"end...\n";
    return 0;
}