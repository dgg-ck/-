#pragma once
#include<iostream>
//类声明
class Node;
class DoubleLinkList;

//取别名
using pNode = Node*;
using pDLinkList = DoubleLinkList*;

class Node
{
public:
	//前驱指针
	pNode pPre;
	//后驱指针
	pNode pNext;
	//数据位
	int iData;

	Node(int data) :iData(data), pPre(nullptr), pNext(nullptr) {};

	~Node();

};


class DoubleLinkList
{
public:
	//指向头结点的指针
	pNode pHead;
	//链表的大小
	int iSize;

	DoubleLinkList() :pHead(nullptr), iSize(0) {};

	pNode DoubleLinkListInit();

	~DoubleLinkList();
};

//增
//尾插
void TailInsert(DoubleLinkList& list, Node& newnode);
//尾删
void TailDelete(DoubleLinkList& list);


//头插
void HeadInsert(DoubleLinkList& list, Node& newnode);
//头删
void HeadDelete(DoubleLinkList& list);

//改
void ChangeNode(DoubleLinkList& list, int index, int data);
//查
void SearchNode(DoubleLinkList& list, int destdata);

//链表输出
void ShowLinkLIst(DoubleLinkList& list);

void InvertShowLinkLIst(DoubleLinkList& list);

bool IsLoop(DoubleLinkList& list);