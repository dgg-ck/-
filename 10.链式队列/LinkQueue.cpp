#include"LinkQueue.h"

//结点类的析构与构造
Node::Node(int data) :iData{ data }, pNext{ nullptr }{ };

Node::~Node()
{
	iData = 0;
	pNext = nullptr;
}

//链表队列
LinkQueue::LinkQueue()
{
	pFront = nullptr;
	pRear = nullptr;
	iSize = 0;


}

LinkQueue::~LinkQueue()
{
	pFront = nullptr;
	pRear = nullptr;
	iSize = 0;

}

//入队
void LinkQueue::EnQueue(pNode newnode)
{
	//空队的时候
	if (iSize == 0)
	{
		pFront = newnode;
		pRear = pFront;
		iSize++;
		return;
	}
	else
	{
		//入队
		pRear->pNext = newnode;
		pRear = newnode;
		iSize++;
		return;

	}

}

//出队
void LinkQueue::DeQueue()
{
	if (iSize == 0)
	{
		std::cout << "队列为空，无法出队" << std::endl;
		return;
	}
	else
	{
		pNode pTmp = nullptr;
		//保存下一个结点
		pTmp = pFront->pNext;
		//出队
		delete pFront;
		iSize--;
		pFront = pTmp;

	}

}

//输出队列
void LinkQueue::ShowQueue()
{
	if (iSize == 0)
	{
		std::cout << "队列为空，无法输出" << std::endl;
		return;
	}
	else
	{
		pNode pnode = pFront;

		std::cout << "队列有" << iSize << "个" << std::endl;
		std::cout << "队列的数据:";
		while (pnode != nullptr)
		{
			std::cout << pnode->iData <<" ";
			pnode = pnode->pNext;
		}
	}


}