#pragma once
#include<iostream>
class Node;
class SLinkList;
using pNode = Node*;
using pSLinkList = SLinkList*;

//链表节点
class Node
{
public:
	int iData;
	pNode pNext;

	Node(int data) :iData(data), pNext(nullptr) {};
	~Node();
};

//单链表信息
class LinkStack
{
public:
	pNode pHead;
	pNode pBottom;
	int iSize;
	
	~LinkStack();
};

//节点初始化
void NodeInit(Node& node);

//链表初始化
void LinkStackInit(LinkStack& ls);


//尾插
void LinkStackEnter(LinkStack& ls, Node& newnode);
//尾删
void LinkStackPop(LinkStack& ls);


//信息输出
void ShowLinkStack(pNode node);

void LinkStackDestory(LinkStack& ls);

