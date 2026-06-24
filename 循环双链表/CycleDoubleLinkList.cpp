#include"CycleDoubleLinkList.h"

//析构函数
Node::~Node()
{

	pPre = nullptr;
	pNext = nullptr;
	iData = -1;
}

DoubleLinkList::~DoubleLinkList()
{
	delete pHead;
	pHead = nullptr;
	iSize = 0;
}

pNode DoubleLinkList::DoubleLinkListInit()
{
	//头结点
	pHead = new Node(0);
	return pHead;
}

//尾插
void TailInsert(DoubleLinkList& list, Node& newnode)
{

	//看看链表中有没有元素
	if (list.iSize == 0)
	{
		//头结点指向首结点
		list.pHead->pNext = &newnode;
		list.pHead->pPre = &newnode;
		//首结点指向头结点
		newnode.pPre = list.pHead;
		newnode.pNext = list.pHead;
		list.iSize++;
	}
	else
	{
		pNode pTmp = list.pHead->pNext;
		//指针指向尾节点
		while (pTmp->pNext != list.pHead)
		{
			pTmp = pTmp->pNext;
		}

		//插入
		newnode.pPre = pTmp;
		newnode.pNext = list.pHead;
		pTmp->pNext = &newnode;
		//头结点的前驱指针指向尾结点
		list.pHead->pPre = &newnode;
		list.iSize++;
	}

}
//尾删
void TailDelete(DoubleLinkList& list)
{
	if (list.iSize == 0)
	{
		std::cout << "链表为空，无法删除" << std::endl;
		return;
	}
	else
	{
		pNode pTmp = list.pHead->pNext;

		//指向最后一个结点
		while (pTmp->pNext != list.pHead)
		{
			pTmp = pTmp->pNext;
		}

		//进行资源删除
		//倒数第二个结点变成最后一个结点
		pTmp->pPre->pNext = list.pHead;
		list.pHead->pPre = pTmp->pPre;
		delete pTmp;
		list.iSize--;
	}
}

//头插
void HeadInsert(DoubleLinkList& list, Node& newnode)
{
	//看看链表中有没有元素
	if (list.iSize == 0)
	{
		//头结点指向首结点
		list.pHead->pNext = &newnode;
		list.pHead->pPre = &newnode;
		//尾结点指向头结点
		newnode.pPre = list.pHead;
		newnode.pNext = list.pHead;
		list.iSize++;
	}
	else
	{
		//保存首结点地址
		pNode pTmp = list.pHead->pNext;

		//插入新的首结点
		list.pHead->pNext = &newnode;
		newnode.pPre = list.pHead;
		newnode.pNext = pTmp;
		list.iSize++;
		//旧首结点的前驱指针要指向新的首结点
		pTmp->pPre = &newnode;

	}

}
//头删
void HeadDelete(DoubleLinkList& list)
{
	if (list.iSize == 0)
	{
		std::cout << "链表为空，无法删除" << std::endl;
		return;
	}
	else if (list.iSize == 1)
	{

		delete list.pHead->pNext;
		list.iSize--;
		list.pHead->pNext = nullptr;
		list.pHead->pPre = nullptr;

	}
	else
	{
		pNode pTmp = nullptr;
		//保存第二个结点的地址
		pTmp = list.pHead->pNext->pNext;
		//删除首结点
		delete list.pHead->pNext;
		list.iSize--;
		//头结点指向第二个结点
		list.pHead->pNext = pTmp;
		//新的首结点保存头结点地址
		pTmp->pPre = list.pHead;
		return;
	}


}


//改
void ChangeNode(DoubleLinkList& list, int index, int data)
{
	if (list.iSize == 0)
	{
		std::cout << "链表为空，无元素可更改" << std::endl;
		return;
	}
	else
	{
		//修改首节点
		if (index == 0)
		{
			list.pHead->pNext->iData = data;
			return;
		}
		else
		{
			//临时索引
			int iTmp = 0;
			pNode pTmp = list.pHead->pNext;

			while (pTmp != list.pHead && iTmp != index)
			{
				pTmp = pTmp->pNext;
				iTmp++;
			}

			if (pTmp == list.pHead)
			{
				std::cout << "没找到索引对应的值" << std::endl;
				return;
			}
			else
			{
				pTmp->iData = data;
				return;
			}

		}

	}

}

//查 整个链表遍历，可以查找重复的元素
void SearchNode(DoubleLinkList& list, int destdata)
{
	//链表中无节点
	if (list.iSize == 0)
	{
		std::cout << "链表中无节点可查询" << std::endl;
	}
	else
	{
		pNode pTmp = list.pHead->pNext;
		int iIndex = 0;
		bool bFlag = false;

		while (pTmp->pNext != list.pHead)
		{
			if (pTmp->iData == destdata)
			{
				std::cout << "查到数据: " << pTmp->iData << " 索引为: "
					<< iIndex << std::endl;
				bFlag = true;
			}

			pTmp = pTmp->pNext;
			iIndex++;
		}
		if (bFlag == false)
		{
			std::cout << "在链表中找不到对应的数据" << std::endl;
		}
	}

}


//输出链表
void ShowLinkLIst(DoubleLinkList& list)
{
	//判断空链表
	if (list.iSize == 0)
	{
		std::cout << "空链表，无法输出信息" << std::endl;
		return;
	}
	else
	{
		pNode pTmp = list.pHead->pNext;

		std::cout << "该链表有 " << list.iSize << "个" << std::endl;
		std::cout << "内容如下:" << std::endl;
		std::cout << "数据位: ";
		while (pTmp != list.pHead)
		{
			std::cout << pTmp->iData << " ";
			pTmp = pTmp->pNext;
		}
		std::cout << std::endl;
	}

}


void InvertShowLinkLIst(DoubleLinkList& list)
{
	//判断空链表
	if (list.iSize == 0)
	{
		std::cout << "空链表，无法输出信息" << std::endl;
		return;
	}
	else
	{
		pNode pTmp = list.pHead->pPre;
		
		std::cout << "该链表有 " << list.iSize << "个" << std::endl;
		std::cout << "内容如下:" << std::endl;
		std::cout << "数据位: ";
		//指针往上走
		//不输出头结点
		while (pTmp != list.pHead)
		{
			std::cout << pTmp->iData << " ";
			pTmp = pTmp->pPre;

		}
		std::cout << std::endl;
		return;
	}

}

//判断链表是否有环
bool IsLoop(DoubleLinkList& list)
{
	if (list.iSize == 0)
	{
		std::cout << "链表中没有结点,无法判断" << std::endl;
		return false;
	}

	//快指针
	pNode pFast = nullptr;
	//慢指针
	pNode pSlow = nullptr;
	//次数
	int iCount = 0;

	pFast = list.pHead->pNext;
	pSlow = list.pHead->pNext;

	while ((pFast !=list.pHead && pFast->pNext != list.pHead) && (iCount < list.iSize))
	{
		//先移动慢指针
		pSlow = pSlow->pNext;
		pFast = pFast->pNext->pNext;
		
		iCount++;
		if (pFast == pSlow)
		{
			return true;
		}

	}

	return false;

}