#include"SingleLinkList.h"
#include<iostream>



int main()
{
	//创建链表
	pSLinkList pList = new SLinkList;

	//创建结点
	for (int i = 0; i < 5; i++)
	{
		pNode pNewNode = new Node(i);
		//TailInsert(pList, pNewNode);
		HeadInsert(pList, pNewNode);
	}

	//尾删
	//TailDelete(pList);
	//TailDelete(pList);
	//TailDelete(pList);
	//TailDelete(pList);
	//TailDelete(pList);

	//头删
	HeadDelete(pList);
	HeadDelete(pList);
	HeadDelete(pList);
	HeadDelete(pList);
	HeadDelete(pList);

	//输出链表信息
	ShowList(pList);

	return 0;
}