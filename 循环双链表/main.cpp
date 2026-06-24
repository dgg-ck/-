#include<iostream>
#include"CycleDoubleLinkList.h"
//双链表



int main()
{
	
	pDLinkList pList = new DoubleLinkList();



	pList->DoubleLinkListInit();




	//先创建五个头结点
	for (int i = 1; i <= 100; i++)
	{
		TailInsert(*pList, *(new Node(i)));
	}
	/*HeadInsert(*pList, *(new Node(6)));
	HeadInsert(*pList, *(new Node(7)));
	HeadInsert(*pList, *(new Node(8)));
	HeadInsert(*pList, *(new Node(1)));*/
	//HeadInsert(*pList, *(new Node(2)));
	//HeadInsert(*pList, *(new Node(3)));

	//故障环代码
	//pList->pHead->pNext->pNext->pNext->pNext->pNext = pList->pHead->pNext->pNext;

	//SearchNode(*pList, 10);
	

	//判断链表中有没有环
	if (IsLoop(*pList))
	{
		std::cout << "链表中有故障环" << std::endl;
	}
	else
	{
		std::cout << "链表中有无故障环" << std::endl;
	}


	//删除结点
	/*TailDelete(*pList);
	TailDelete(*pList);
	TailDelete(*pList);
	TailDelete(*pList);
	TailDelete(*pList);
	TailDelete(*pList);
	TailDelete(*pList);
	HeadDelete(*pList);
	HeadDelete(*pList);*/
	//HeadDelete(*pList);

	//输出信息
	ShowLinkLIst(*pList);
	InvertShowLinkLIst(*pList);
	//std::cin.get();

	return 0;
}