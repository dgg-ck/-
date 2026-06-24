#pragma once
#include<iostream>
class Node;
class SLinkList;

using pNode = Node*;
using pSLinkList = SLinkList*;


//结点类
class Node
{
public:
	int iData;
	pNode pNext;

	Node(int data);
	~Node();
};

//链表类，里面包含头结点
class SLinkList
{
public:
	pNode pHead;
	int iSize;

	SLinkList();
	~SLinkList();
};

//尾插
void TailInsert(const pSLinkList& pList, const pNode& pNewNode);

//头插
void HeadInsert(const pSLinkList& pList, const pNode& pNewNode);

//尾删
void TailDelete(const pSLinkList& pList);

//头删
void HeadDelete(const pSLinkList& pList);

//信息输出
void ShowList(const pSLinkList& pList);

//原地反转
void InPlaceReverse(const pSLinkList& pList);

//头插法反转
void HeadInsertReverse(pSLinkList& pList);

//递归法反转
pNode RecusiveReverse(pNode node);

//摧毁链表
void LinkListDestory(pSLinkList& pList);