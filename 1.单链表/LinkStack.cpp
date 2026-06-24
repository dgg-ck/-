#include"LinkStack.h"

//节点初始化
void NodeInit(Node& node)
{
	node.iData = 0;
	node.pNext = nullptr;
	return;
}

//链表初始化(不带头结点)
void LinkStackInit(LinkStack& ls)
{
	
	ls.pHead = nullptr;
	ls.pBottom = nullptr;
	ls.iSize = -1;
	return;
}

//节点的析构函数
Node::~Node()
{
	iData = 0;
	pNext = nullptr;
}

//链表入口的析构函数
LinkStack::~LinkStack()
{
	iSize = 0;
	pHead = nullptr;
	pBottom = nullptr;
}



//入栈
void LinkStackEnter(LinkStack& ls, Node& newnode)
{
	//空栈
	if (ls.iSize == -1)
	{
		ls.pBottom = &newnode;
		ls.pHead = &newnode;
		ls.iSize++;
	}
	else
	{
		//先入栈
		ls.pHead->pNext = &newnode;
		//栈顶指针重新指向栈顶
		ls.pHead = &newnode;
		ls.iSize++;
	}

	return;
}




//删(头删，尾删，任意删)
//尾删
void LinkStackPop(LinkStack& ls)
{
	if (ls.iSize == -1)
	{
		std::cout << "空栈，无法弹出" << std::endl;
		return;
	}
	//栈中只有一个结点的情况
	else if(ls.iSize == 0)
	{
		delete ls.pBottom;
		ls.pBottom = nullptr;
		ls.pHead = nullptr;
		ls.iSize--;
	}
	else
	{
		pNode pTmp = ls.pBottom;

		//将临时指针指向倒数第二个结点
		while (pTmp->pNext->pNext != nullptr)
		{
			pTmp = pTmp->pNext;
		}

		//出栈
		delete ls.pHead;
		//栈顶指针往前一个结点指
		ls.pHead = pTmp;
		ls.pHead->pNext = nullptr;
		//大小减小
		ls.iSize--;

		return;
	}

}




//输出信息
void ShowLinkStack(pNode node)
{

	if (node == nullptr)
	{
		std::cout << "该链表为空，无法输出" << std::endl;
		return;
	}
	//到结束条件了，递归到最后一个结点了
	else if (node->pNext == nullptr)
	{
		std::cout << node->iData << " ";
		return;
	}

	ShowLinkStack(node->pNext);

	std::cout << node->iData << " ";
		
	return;
}


//内存管理
void LinkStackDestory(LinkStack& ls)
{
	
}

