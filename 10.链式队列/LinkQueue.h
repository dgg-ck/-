#pragma once
#include<iostream>
class Node;
class LinkQueue;

using pNode = Node*;
using pLinkQueue = LinkQueue*;


//结点类
class Node
{
public:
	int iData;
	pNode pNext;

	Node(int data);
	~Node();
};

class LinkQueue
{
public:
	pNode pFront;
	pNode pRear;
	int iSize;
	
	LinkQueue();
	~LinkQueue();

	//入队
	void EnQueue(pNode newnode);

	//出队
	void DeQueue();

	//输出
	void ShowQueue();

};