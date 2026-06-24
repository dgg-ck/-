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
		return;
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



//原地反转
void InPlaceReverse(const pSLinkList& pList)
{
	pNode pFront = nullptr;
	pNode pRear = nullptr;
	pNode pTmp = nullptr;

	if (pList->iSize == 0)
	{
		std::cout << "空链表无法反转" << std::endl;
		return;
	}
	else
	{
		//先指向首结点
		pFront = pList->pHead->pNext;
		//指向第Front的后一个结点
		pRear = pFront->pNext;
		
		while (pRear != nullptr)
		{
			//先保存要前插的结点的后面结点的地址
			pFront->pNext = pRear->pNext;
			//保存头结点后的结点
			pRear->pNext = pList->pHead->pNext;
			//头插
			pList->pHead->pNext = pRear;
			//pRear回到pFront的后面
			pRear = pFront->pNext;
		}

	}

}

//头插法反转
void HeadInsertReverse( pSLinkList& pList)
{
	if (pList->iSize == 0)
	{
		std::cout << "链表为空,无法反转" << std::endl;
		return;
	}
	else
	{
		//保存首节点地址
		pNode pCurNode = pList->pHead->pNext;
		pNode pTmp = nullptr;

		//让头结点空出来
		pList->pHead->pNext = nullptr;

		//头插
		while (pCurNode != nullptr)
		{
			//先保存头插结点的后一个结点
			pTmp = pCurNode->pNext;
			//保存头结点的后驱指针
			pCurNode->pNext = pList->pHead->pNext;
			//头插
			pList->pHead->pNext = pCurNode;
			//指向下一个头插指针
			pCurNode = pTmp;
		}
		return;
	}

}


//递归反转
pNode RecusiveReverse(pNode node)
{
	//递归结束基准
	if (node == nullptr || node->pNext == nullptr)
	{
		//返回的是尾结点的地址
		return node;
	}

	//后一个结点返回来的地址
	pNode phead = RecusiveReverse(node->pNext);

	//node->pNext指的是下一个节点，再加个pNext表达就是后一个结点反过来连接我，逆转的意思
	node->pNext->pNext = node;
	//先把自身的后驱指针断开
	node->pNext = nullptr;


	//返回尾结点，最后成为了头结点
	return phead;
}


//链表摧毁
void LinkListDestory(pSLinkList& pList)
{
	if (pList->iSize == 0)
	{
		std::cout << "链表为空，无法摧毁" << std::endl;
		delete pList;
		pList = nullptr;
		return;
	}
	else
	{
		
		pNode pTmp = pList->pHead->pNext;
		int iCount = 0;

		while (pList->iSize != 0)
		{
			HeadDelete(pList);
		}

		//最后删除链表
		delete pList;
		pList = nullptr;
		std::cout << "链表已经被摧毁了" << std::endl;

		return;

	}

}