#include<iostream>
#include"DoubleLinkList.h"
//双链表



int main()
{
	pDLinkList pList = new DoubleLinkList();
	pList->DoubleLinkListInit();

	//先创建五个头结点
	for (int i = 1; i <= 5; i++)
	{
		TailInsert(*pList, *(new Node(i)));
	}
	HeadInsert(*pList, *(new Node(6)));
	HeadInsert(*pList, *(new Node(7)));
	HeadInsert(*pList, *(new Node(8)));
	HeadInsert(*pList, *(new Node(1)));
	HeadInsert(*pList, *(new Node(2)));
	HeadInsert(*pList, *(new Node(3)));

	
	

	//删除结点
	TailDelete(*pList);
	TailDelete(*pList);
	TailDelete(*pList);
	TailDelete(*pList);
	TailDelete(*pList);
	TailDelete(*pList);
	TailDelete(*pList);
	HeadDelete(*pList);
	HeadDelete(*pList);
	HeadDelete(*pList);
	HeadDelete(*pList);

	//输出信息
	InvertShowLinkLIst(*pList);
	std::cin.get();

	return 0;
}