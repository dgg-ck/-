#include"SingleLinkList.h"

//结点类的析构与构造
Node::Node(int data) :iData{ data }, pNext{ nullptr }{ };

Node::~Node() 
{
	iData = 0;
	pNext = nullptr;
}

//链表类的析构与构造
SLinkList::SLinkList()
{
	pHead = new Node(0);
	iSize = 0;
}

SLinkList::~SLinkList()
{
	delete pHead;
	iSize = 0;
}


//增
//尾插
void TailInsert(const pSLinkList& pList, const pNode& pNewNode)
{
	//空链表
	if (pList->iSize == 0)
	{
		pList->pHead->pNext = pNewNode;
		pList->iSize++;
	}
	else
	{
		//指向首结点
		pNode pTmp = pList->pHead->pNext;

		//指向最后一个结点
		while (pTmp->pNext != nullptr)
		{
			pTmp = pTmp->pNext;
		}

		//尾插
		pTmp->pNext = pNewNode;
		pList->iSize++;

	}

}
//头插
void HeadInsert(const pSLinkList& pList, const pNode& pNewNode)
{
	//空表
	if (pList->iSize == 0)
	{
		pList->pHead->pNext = pNewNode;
		pList->iSize++;
		return;
	}
	else
	{
		pNode pTmp = nullptr;

		//保存后面的结点
		pTmp = pList->pHead->pNext;
		//头插
		pList->pHead->pNext = pNewNode;
		//头结点接上后面的结点
		pNewNode->pNext = pTmp;
		pList->iSize++;

		return;
	}

}


//删
//尾删
void TailDelete(const pSLinkList& pList)
{
	if (pList->iSize == 0)
	{
		std::cout << "链表为空，无法删除" << std::endl;
		return;
	}
	else if (pList->iSize == 1)
	{
		delete pList->pHead->pNext;
		pList->pHead->pNext = nullptr;
		pList->iSize--;
	}
	else
	{
		//指向头结点
		pNode pTmp = pList->pHead->pNext;

		//指向倒数第二个结点
		while (pTmp->pNext->pNext != nullptr)
		{
			pTmp = pTmp->pNext;
		}

		//尾删
		delete pTmp->pNext;
		pTmp->pNext = nullptr;
		pList->iSize--;

		return;
	}

}

//头删
void HeadDelete(const pSLinkList& pList)
{
	if (pList->iSize == 0)
	{
		std::cout << "链表为空，无法删除" << std::endl;
		return;
	}
	else
	{
		pNode pTmp = nullptr;

		//指向首节点
		pTmp = pList->pHead->pNext->pNext;

		//头删
		delete pList->pHead->pNext;
		//接上
		pList->pHead->pNext = pTmp;
		pList->iSize--;

		return;
	}

	
}


//输出信息
void ShowList(const pSLinkList& pList)
{
	//空链表
	if (pList->iSize == 0)
	{
		std::cout << "该链表为空，无法输出" << std::endl;
		return;
	}
	else
	{
		//指向首结点
		pNode pTmp = pList->pHead->pNext;

		std::cout << "结点个数:" << pList->iSize << std::endl;
		std::cout << "数据位:";
		while (pTmp != nullptr)
		{
			std::cout << pTmp->iData << " ";
			pTmp = pTmp->pNext;
		}

		return;
	}
	
}