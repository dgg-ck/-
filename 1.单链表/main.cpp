//单链表
#include<iostream>
#include"LinkStack.h"

int main()
{
	//创建链表入口
	LinkStack* pStack = new LinkStack;
	//链表和头节点同时初始化
	LinkStackInit(*pStack);

	//先创建五个头结点
	for (int i = 1; i <= 5; i++)
	{
		LinkStackEnter(*pStack, *(new Node(i)));
	}

	//std::cout << pStack->pBottom->iData << std::endl;
	//出栈
	LinkStackPop(*pStack);
	LinkStackPop(*pStack);
	LinkStackPop(*pStack);
	LinkStackPop(*pStack);
	LinkStackPop(*pStack);
	//信息输出
	ShowLinkStack(pStack->pBottom);


	

	//LinkStackDestory(*pStack);

	return 0;
}