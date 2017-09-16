#include "linklist.h"
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <QDebug>
using namespace std;

/* 构造函数（初始化线性表） */
LinkList::LinkList()
{
    head = NULL;  //头指针直接赋NULL
}

/* 析构函数（删除线性表） */
LinkList::~LinkList()
{
    LNode *q, *p = head;

    /* 整个链表(含头结点)依次释放
    不能用while循环 */
    do {
        q = p->next; //抓住链表的下一个结点，若空表则q直接为NULL
        delete p;
        p = q;
    } while (p !=head);   //若链表为空，则循环不执行

    head = NULL;	//头指针置NULL
}

/* 清除线性表（保留头结点） */
Status LinkList::ClearList()
{
    LNode *q, *p = head;

    /* 整个链表(含头结点)依次释放
    不能用while循环 */
    do {
        q = p->next; //抓住链表的下一个结点，若空表则q直接为NULL
        delete p;
        p = q;
    } while (p !=head);   //若链表为空，则循环不执行

    head = NULL;	//头指针置NULL
    return OK;
}

/* 判断是否为空表 */
Status LinkList::ListEmpty()
{
    /* 判断头结点的next域即可 */
    if (head->next==head)
    return TRUE;
    else
    return FALSE;
}

/* 求表的长度 */
int LinkList::ListLength()
{
    LNode *p = head; //指向首元结点
    int    len = 0;

    /* 循环整个链表，进行计数 */
    while(p!=head) {
    p = p->next;
    len++;
    }

    return len;
}

/* 取表中元素 */
Status LinkList::GetElem(int i, ElemType &e)
{
    LNode *p = head;	//指向首元结点
    int  pos = 1;		//初始位置为1

    /* 链表不为NULL 且 未到第i个元素 */
    while(p!=head && pos<i) {
        p=p->next;
        pos++;
    }

    if (p!=head || pos>i)
        return ERROR;

    e = p->data;
    return OK;
}

/* 查找符合指定条件的元素 */
int LinkList::LocateElem(ElemType e, Status (*compare)(ElemType e1, ElemType e2))
{
    LNode *p = head;	//指向首元结点
    int  pos = 1;		//初始位置为1

    /* 循环整个链表  */
    while(p!=head && (*compare)(e, p->data)==FALSE) {
    p=p->next;
    pos++;
    }

    return (p!=head) ? pos:0;
}

/* 查找符合指定条件的元素的前驱元素 */
Status LinkList::PriorElem(ElemType cur_e, ElemType &pre_e)
{
#if 0
    LNode *p = head->next;	//指向首元结点

    if (p==head)	//空表直接返回
        return ERROR;

    /* 从第2个结点开始循环整个链表(如果比较相等，保证有前驱) */
    while(p->next!=head && p->next->data != cur_e)
        p = p->next;

    if (p->next==head) //未找到
        return ERROR;

    pre_e = p->data;
    return OK;
#else
    LNode *p = head; //指向头结点

    /* 循环整个链表并比较值是否相等 */
    while(p->next!=head && p->next->data != cur_e)
        p = p->next;

    if (p->next==head || p==head) //未找到或首元结点或空表
         return ERROR;

    pre_e = p->data;
    return OK;
#endif
}

/* 查找符合指定条件的元素的后继元素 */
Status LinkList::NextElem(ElemType cur_e, ElemType &next_e)
{
    LNode *p = head;  //首元结点

    if (p==head)	//空表直接返回
        return ERROR;

    /* 有后继结点且当前结点值不等时继续 */
    while(p->next!=head && p->data!=cur_e)
        p = p->next;

    if (p->next==head)
        return ERROR;

    next_e = p->next->data;
    return OK;
}

/* 在指定位置前插入一个新元素 */
Status LinkList::ListInsert(int i, int e)
{
    LNode *s, *p = head;	//p指向头结点
    int   pos  = 1;

    if (i == 1)
        goto INSERT;

    /* 寻找第i-1个结点 */
    do {
        p = p->next;
        pos++;
    } while (p != head&& pos<i - 1);

    if (p == head || pos>i - 1)  //i值非法则返回
        return ERROR;

    //执行到此表示找到指定位置，p指向第i-1个结点
INSERT:
    s = new LNode;
    if (s==NULL)
    return FOVERFLOW;

    s->data = new QLabel(QString::number(e)); 	//新结点数据域赋值
    s->next = p->next;	//新结点的next是第i个
    p->next = s;	//第i-1个的next是新结点

    return OK;
}

/* 删除头节点 */
Status LinkList::ListDelete(int n,QString *e)
{
    LNode *q=head;
    LNode *p = head;	//p指向头结点
        /* 寻找尾结点 */
        for(int i=0;i<n-1;i++) {
            p=p->next;
        }

        //执行到此表示找到了第i个结点，此时p指向尾结点

        p->next = q->next; //第i-1个结点的next域指向第i+1个
        head=q->next;
        *e=q->data->text();
        delete q;           //释放第i个结点

    return OK;
}

/* 遍历线性表 */
Status LinkList::ListTraverse()
{
    LNode *p = head;
    while(p!=head)
    {
        p=p->next;
    }
    if (p!=head)
        return ERROR;

    return OK;
}
