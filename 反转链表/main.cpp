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
	//输出链表信息
	ShowList(pList);

	//尾删
	//TailDelete(pList);
	//TailDelete(pList);
	//TailDelete(pList);
	//TailDelete(pList);
	//TailDelete(pList);

	//头删
	/*HeadDelete(pList);
	HeadDelete(pList);
	HeadDelete(pList);
	HeadDelete(pList);
	HeadDelete(pList);*/

	//链表反转
	//递归反转(头结点需要重连)
	std::cout << std::endl << "数据反转了" << std::endl;
	pNode pTmp = RecusiveReverse(pList->pHead->pNext);
	pList->pHead->pNext = pTmp;
	std::cout << std::endl << "数据反转了" << std::endl;
	//头插反转
	HeadInsertReverse(pList);
	//原地反转
	std::cout << std::endl << "数据反转了" << std::endl;
	InPlaceReverse(pList);

	//输出链表信息
	ShowList(pList);
	//摧毁列表
	LinkListDestory(pList);

	return 0;
}